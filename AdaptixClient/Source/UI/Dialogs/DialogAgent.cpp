#include <UI/Dialogs/DialogAgent.h>
#include <Client/Requestor.h>
#include <Client/AuthProfile.h>
#include <Client/AxScript/AxElementWrappers.h>

DialogAgent::DialogAgent(const QString &listenerName, const QString &listenerType)
{
    this->createUI();

    this->listenerInput->setText(listenerName);

    this->listenerName = listenerName;
    this->listenerType = listenerType;

    connect(buttonLoad,     &QPushButton::clicked,          this, &DialogAgent::onButtonLoad);
    connect(buttonSave,     &QPushButton::clicked,          this, &DialogAgent::onButtonSave);
    connect(agentCombobox,  &QComboBox::currentTextChanged, this, &DialogAgent::changeConfig) ;
    connect(generateButton, &QPushButton::clicked,          this, &DialogAgent::onButtonGenerate);
    connect(closeButton,    &QPushButton::clicked,          this, &DialogAgent::onButtonClose);
}

DialogAgent::~DialogAgent() = default;

void DialogAgent::createUI()
{
    this->resize( 500, 450 );
    this->setWindowTitle(tr( "Generate Agent" ));

    listenerLabel = new QLabel(tr("Listener:"), this);
    listenerLabel->setMinimumWidth(80); 
    listenerInput = new QLineEdit(this);
    listenerInput->setReadOnly(true);

    agentLabel = new QLabel(tr("Agent: "), this);
    agentLabel->setMinimumWidth(80); 
    agentCombobox = new QComboBox(this);

    buttonLoad = new QPushButton(QIcon(":/icons/file_open"), "", this);
    buttonLoad->setIconSize( QSize( 25,25 ));
    buttonLoad->setToolTip("Load profile from file");

    buttonSave = new QPushButton(QIcon(":/icons/save_as"), "", this);
    buttonSave->setIconSize( QSize( 25,25 ));
    buttonSave->setToolTip("Save profile to file");

    line_1 = new QFrame(this);
    line_1->setFrameShape(QFrame::VLine);
    line_1->setMinimumHeight(20);

    configStackWidget = new QStackedWidget(this );

    stackGridLayout = new QGridLayout(this );
    stackGridLayout->setHorizontalSpacing(0);
    stackGridLayout->setContentsMargins(0, 0, 0, 0 );
    stackGridLayout->addWidget(configStackWidget, 0, 0, 1, 1 );

    agentConfigGroupbox = new QGroupBox(tr("Agent config"));
    agentConfigGroupbox->setMinimumWidth(400); 
    agentConfigGroupbox->setLayout(stackGridLayout);

    generateButton = new QPushButton(tr("Generate"));
    generateButton->setProperty( "ButtonStyle", "dialog" );
    generateButton->setMinimumWidth(100);

    closeButton = new QPushButton(tr("Close"));
    closeButton->setProperty( "ButtonStyle", "dialog" );
    closeButton->setMinimumWidth(100);

    horizontalSpacer   = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hLayoutBottom = new QHBoxLayout();
    hLayoutBottom->addItem(horizontalSpacer_2);
    hLayoutBottom->addWidget(generateButton);
    hLayoutBottom->addSpacing(10);
    hLayoutBottom->addWidget(closeButton);
    hLayoutBottom->addItem(horizontalSpacer_3);

    mainGridLayout = new QGridLayout( this );
    mainGridLayout->addWidget( listenerLabel,       0, 0, 1, 1);
    mainGridLayout->addWidget( listenerInput,       0, 1, 1, 1);
    mainGridLayout->addWidget( line_1,              0, 2, 2, 1);
    mainGridLayout->addWidget( buttonLoad,          0, 3, 1, 1);
    mainGridLayout->addWidget( agentLabel,          1, 0, 1, 1);
    mainGridLayout->addWidget( agentCombobox,       1, 1, 1, 1);
    mainGridLayout->addWidget( buttonSave,          1, 3, 1, 1);
    mainGridLayout->addItem(   horizontalSpacer,    2, 0, 1, 4);
    mainGridLayout->addWidget( agentConfigGroupbox, 3, 0, 1, 4);
    mainGridLayout->addLayout( hLayoutBottom,       4, 0, 1, 4);

    this->setLayout(mainGridLayout);


    buttonLoad->setMinimumWidth(50);
    buttonSave->setMinimumWidth(50);


    int buttonHeight = generateButton->sizeHint().height();
    buttonLoad->setMinimumHeight(buttonHeight);
    buttonSave->setMinimumHeight(buttonHeight);
    closeButton->setMinimumHeight(buttonHeight);
    generateButton->setMinimumHeight(buttonHeight);
}

void DialogAgent::Start() { this->exec(); }

void DialogAgent::AddExAgents(const QStringList &agents, const QMap<QString, QWidget*> &widgets, const QMap<QString, AxContainerWrapper*> &containers)
{
    agentCombobox->clear();

    this->agents     = agents;
    this->widgets    = widgets;
    this->containers = containers;

    for (auto agent : agents) {
        widgets[agent]->setParent(nullptr);
        widgets[agent]->setParent(this);
        containers[agent]->setParent(nullptr);
        containers[agent]->setParent(this);

        configStackWidget->addWidget(widgets[agent]);

        agentCombobox->addItem(agent);
    }
 }

void DialogAgent::SetProfile(const AuthProfile &profile) { this->authProfile = profile; }

void DialogAgent::onButtonGenerate()
{
    QString agentName  = agentCombobox->currentText();
    auto configData = QString();
    if (containers[agentName])
        configData = containers[agentName]->toJson();

    QString message = QString();
    bool ok = false;
    bool result = HttpReqAgentGenerate(listenerName, listenerType, agentName, configData, authProfile, &message, &ok);
    if( !result ){
        MessageError(tr("Server is not responding"));
        return;
    }
    if ( !ok ) {
        MessageError(message);
        return;
    }

    QStringList parts = message.split(":");
    if (parts.size() != 2) {
        MessageError("The response format is not supported");
        return;
    }

    QString filename = QString( QByteArray::fromBase64(parts[0].toUtf8()));
    QByteArray content = QByteArray::fromBase64(parts[1].toUtf8());

    QString filePath = QFileDialog::getSaveFileName( nullptr, "Save File", filename, "All Files (*.*)" );
    if ( filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        MessageError("Failed to open file for writing");
        return;
    }

    file.write( content );
    file.close();

    QInputDialog inputDialog;
    inputDialog.setWindowTitle("Save agent");
    inputDialog.setLabelText("File saved to:");
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    inputDialog.setTextValue(filePath);
    inputDialog.adjustSize();
    inputDialog.move(QGuiApplication::primaryScreen()->geometry().center() - inputDialog.geometry().center());
    inputDialog.exec();

    this->close();
}

void DialogAgent::onButtonLoad()
{
    QString filePath = QFileDialog::getOpenFileName( nullptr, "Select file", QDir::homePath(), "JSON files (*.json)" );
    if ( filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray fileContent = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(fileContent, &parseError);
    if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
        MessageError("Error JSON parse");
        return;
    }
    QJsonObject jsonObject = document.object();

    if ( !jsonObject.contains("listener_type") || !jsonObject["listener_type"].isString() ) {
        MessageError("Required parameter 'listener_type' is missing");
        return;
    }
    if ( !jsonObject.contains("agent") || !jsonObject["agent"].isString() ) {
        MessageError("Required parameter 'agent' is missing");
        return;
    }
    if ( !jsonObject.contains("config") || !jsonObject["config"].isString() ) {
        MessageError("Required parameter 'config' is missing");
        return;
    }

    if(listenerType != jsonObject["listener_type"].toString()) {
        MessageError("Listener type mismatch");
        return;
    }

    QString agentType = jsonObject["agent"].toString();
    int typeIndex = agentCombobox->findText( agentType );
    if ( typeIndex == -1 ) {
        MessageError("No such agent exists");
        return;
    }
    agentCombobox->setCurrentIndex(typeIndex);
    this->changeConfig(agentType);

    QString configData = jsonObject["config"].toString();
    containers[agentType]->fromJson(configData);
}

void DialogAgent::onButtonSave()
{
    QString configType = agentCombobox->currentText();
    auto configData = QString();
    if (containers[configType])
        configData = containers[configType]->toJson();

    QJsonObject dataJson;
    dataJson["listener_type"] = listenerType;
    dataJson["agent"]         = configType;
    dataJson["config"]        = configData;
    QByteArray fileContent = QJsonDocument(dataJson).toJson();

    QString tmpFilename = QString("%1_config.json").arg(configType);
    QString filePath = QFileDialog::getSaveFileName( nullptr, "Save File", tmpFilename, "JSON files (*.json)" );
    if ( filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        MessageError("Failed to open file for writing");
        return;
    }

    file.write( fileContent );
    file.close();

    QInputDialog inputDialog;
    inputDialog.setWindowTitle("Save config");
    inputDialog.setLabelText("File saved to:");
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    inputDialog.setTextValue(filePath);
    inputDialog.adjustSize();
    inputDialog.move(QGuiApplication::primaryScreen()->geometry().center() - inputDialog.geometry().center());
    inputDialog.exec();

}

void DialogAgent::onButtonClose() { this->close(); }

void DialogAgent::changeConfig(const QString &agentName)
{
    if (widgets.contains(agentName))
        configStackWidget->setCurrentWidget(widgets[agentName]);
}