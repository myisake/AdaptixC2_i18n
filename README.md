# AdaptixC2_i18n v0.9 (多语言支持版)

## 声明

本项目是 **[AdaptixC2]([https://github.com/Adaptix-Framework/AdaptixC2])** 的一个二次开发版本。

主要在此基础上增加了**多语言界面支持** (Internationalization, i18n)，方便不同语言的用户使用(暂时只有中/英切换)。

本项目同样遵循 **GPL-3.0** 许可证发布。所有原始项目的功能、特性和版权归原作者所有。

---

## 关于 AdaptixC2

Adaptix 是一款为渗透测试人员打造的可扩展的后渗透和对抗模拟框架。其服务器端由 Golang 编写，为操作员提供了极大的灵活性。图形用户界面客户端则由 C++ QT 编写，支持在 Linux、Windows 和 macOS 操作系统上使用。[完整的官方文档请点击此处](https://adaptix-framework.gitbook.io/adaptix-framework)。

![](https://adaptix-framework.gitbook.io/adaptix-framework/~gitbook/image?url=https%3A%2F%2F2104178602-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FS8p8XLFtLmf0NkofQvoa%252Fuploads%252FYyoRo3MmqD8iQaEApgaK%252FScreenshot_20250624_000326.png%3Falt%3Dmedia%26token%3De87b1861-91fa-413a-b9f7-8fabf362fb7d&width=768&dpr=4&quality=100&sign=eca8f023&sv=2)

根据系统语言环境自动切换中/英显示
![](https://github.com/myisake/AdaptixC2_i18n/blob/main/img/01.png)

![](https://github.com/myisake/AdaptixC2_i18n/blob/main/img/02.png)

![](https://github.com/myisake/AdaptixC2_i18n/blob/main/img/03.png)

## 快速开始

请查阅官方 [Wiki 文档中的安装指南](https://adaptix-framework.gitbook.io/adaptix-framework/adaptix-c2/getting-starting/installation)。

## 功能特性
* 支持多人协作的服务器/客户端架构
* 跨平台的图形用户界面 (GUI) 客户端
* 完全加密的通信
* 监听器和 Agent 采用插件式设计 (Extender)
* 客户端可扩展，方便添加新工具
* 任务和作业存储
* 凭据管理器
* 目标管理器
* 文件和进程浏览器
* 支持 Socks4 / Socks5 / Socks5 Auth
* 支持本地和反向端口转发
* 支持 BOF (Beacon Object Files)
* Agent 连接和会话图
* Agent 健康状态检查器
* Agent 的销毁日期 (KillDate) 和工作时间 (WorkingTime) 控制
* 支持 Windows/Linux/macOS Agent
* 远程终端
* AxScript 脚本引擎

## 扩展套件 (Extension-Kit)

官方 [Extension-Kit](https://github.com/Adaptix-Framework/Extension-Kit) 已在 GitHub 开源。

![](https://adaptix-framework.gitbook.io/adaptix-framework/~gitbook/image?url=https%3A%2F%2F2104178602-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FS8p8XLFtLmf0NkofQvoa%252Fuploads%252FUeHUj7y5kVkH9y3IAIl6%252FScreenshot_20250727_211916.png%3Falt%3Dmedia%26token%3Db01bf49d-4367-4d58-a591-ca1968703bf9&width=768&dpr=4&quality=100&sign=aed8255&sv=2)

![](https://adaptix-framework.gitbook.io/adaptix-framework/~gitbook/image?url=https%3A%2F%2F2104178602-files.gitbook.io%2F%7E%2Ffiles%2Fv0%2Fb%2Fgitbook-x-prod.appspot.com%2Fo%2Fspaces%252FS8p8XLFtLmf0NkofQvoa%252Fuploads%252F3bSUEMTwplwgL8Mrq71o%252FScreenshot_20250727_211902.png%3Falt%3Dmedia%26token%3D3c23b1d0-9646-40cb-99cc-cff059fb1dea&width=768&dpr=4&quality=100&sign=833ee99f&sv=2)

## 当前的扩展模块

* HTTP/S Beacon 监听器
* SMB Beacon 监听器
* TCP Beacon 监听器
* Beacon Agent
* TCP/mTLS Gopher 监听器
* Gopher Agent

## 许可证 (License)

本项目基于 **GNU General Public License v3.0** 许可证开源。详情请见 `LICENSE` 文件。
