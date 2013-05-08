#  avbot = 聊天机器人（QQ云秘书）[![Build Status](https://travis-ci.org/avplayer/avbot.png?branch=master)](https://travis-ci.org/avplayer/avbot)

avbot 连通 IRC、XMPP 和  QQ群，并能实时记录聊天信息。每日自动生成新的日志文件。

## 功能介绍

### 登录QQ，记录群消息
### 登录IRC，记录IRC消息
### 登录XMPP，记录XMPP聊天室消息
### 将群消息转发到IRC和XMPP聊天室
### 将IRC消息转发到QQ群和XMPP聊天室
### 将XMPP聊天室消息转发到QQ群和IRC
### QQ图片转成 url 链接给 IRC和XMPP聊天室
### 登录 EMAIL (使用 pop3 协议), 获取邮件, 并转发到聊天室
### 将聊天内容转化为邮件发送到指定的邮箱(在聊天室使用 .qqbot mail to 命令)
### 支持lua作为脚本

# rpm 包

为了方便群主，我特意为　CentOS6/RHEL6　准备了 RPM 包。该　RPM 是静态链接的boost，因此并不需要系统里升级 boost 库。

等啥，到 [这里](https://sourceforge.net/projects/avbot/files/rpm/x86_64/) 下载安装吧

# 代码克隆办法


	git clone git://github.com/avplayer/avbot.git
	cd avbot
	git submodule init
	git submodule update

因为使用了　submodule 引入　avhttp 和　avproxy , 故而需要使用　git submodule update 来更新　avhttp 和 avproxy

# 编译办法

项目使用 cmake 编译。编译办法很简单

	mkdir build
	cd build
	cmake [avbot源码的路径]
	make -j8
## lua支持开关
cmake时加上-DENABLE_LUA=on，可以编译带lua支持的版本。

# 编译依赖

依赖 boost。 boost 要 1.50 以上。

gloox 已经通过 bundle 的形式包含了，不需要外部依赖了。
如果使用的时候出现了段错误，请试试看使用系统的 gloox ,　编译的时候通过　cmake -DINTERNALGLOOX=OFF 关闭内置gloox的使用。


# 使用

配置文件请参考 [qqbotrc.example](https://github.com/avplayer/avbot/blob/master/qqbotrc.example)

读取配置文件 /etc/qqbotrc

配置文件的选项就是去掉 -- 的命令行选项。比如命令行接受 --qqnum 
配置文件就写

	qqnum=qq号码

就可以了。
命令行选项看看 --help 输出

## IRC频道

频道名不带 \# 比如

	--ircrooms=ubuntu-cn,gentoo-cn,fedora-zh

逗号隔开, avbot 会分别加入这些聊天室.

## XMPP 聊天室

	--xmpprooms=linuxcn@im.linuxapp.org,avplayer@im.linuxapp.org

也是逗号隔开

## 频道组

使用 --map 功能将频道和QQ群绑定成一组。被绑定的组内消息互通。

用法：  --map=qq:123456,irc:avplayer;qq:3344567,irc:otherircchannel,mail,xmpp:linuxcn

频道名不带 \# , XMPP 聊天室不带 @ 后面的服务器地址。

也可以在 /etc/qqbotrc 或者 ~/.qqbotrc 写，每行一个，不带 --。
如 map=qq:123456,irc:avplayer;qq:3344567,irc:otherircchannel,mail,xmpp:linuxcn;

频道组用 ; 隔开。组成份间用,隔离。

这个命令形式的意思四建立2个频道组. 第一个频道组包含 QQ群123456,irc频道\#avplayer 第二个频道组包含qq群3344567,irc频道\#otherircchannel, xmpp聊天室linuxcn@im.linuxapp.org. 以及接受邮件转发.
在同一个频道组的群也好,irc频道也罢, XMPP聊天室也好, 相互之间转发消息. 不在一个频道组的则不转发. 像沙箱一样的隔离掉,互不干扰.


# 获得帮助

我们在 IRC（irc.freenode.net ） 的 \#avplayer 频道。 QQ群 3597082 还有 XMPP聊天室 avplayer@im.linuxapp.org

# thanks

谢谢 神话群群主提供的代码和建议；Youku的谢总(女)贡献的IRC代码。
还有 pidgin-lwqq 解析的 WebQQ 协议。

