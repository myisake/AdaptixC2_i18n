#include <main.h>
#include <MainAdaptix.h>
#include <QLoggingCategory>
#include <QTranslator>     // 新增
#include <QLocale>         // 新增

MainAdaptix* GlobalClient = nullptr;

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules(
        "qt.text.font.db=false\n"
        "qt.text.font.db.debug=false\n"
        "qt.text.font.db.warning=false\n"
        "qt.text.font.db.info=false\n"
        "qt.text.font.db.critical=false"
    );

    QApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(true);
    // --- 添加国际化支持 ---
    static QTranslator translator;  // 保证 translator 不会在 main() 结束后被销毁

    // 获取当前系统的语言环境，例如 "zh_CN"
    QString locale = QLocale::system().name();

    // 资源路径
    QString translationFile = QString(":/translations/adaptix_%1.qm").arg(locale);

    if (translator.load(translationFile)) {
        a.installTranslator(&translator);
    }
    // --- 结束 ---
    GlobalClient = new MainAdaptix();
    GlobalClient->Start();
}
