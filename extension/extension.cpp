
#include <boost/asio.hpp>

#include "libavbot/avbot.hpp"
#include "extension.hpp"

#include "libavlog/avlog.hpp"

#ifdef ENABLE_LUA
#	include "luascript.hpp"
#endif

#include "urlpreview.hpp"
#include "joke.hpp"

// dummy file

extern avlog logfile;			// 用于记录日志文件.


static void sender(avbot & mybot,std::string channel_name, std::string txt, bool logtohtml)
{
	mybot.broadcast_message(channel_name, txt);
	if (logtohtml)
		logfile.add_log(channel_name, txt);
}

void new_channel_set_extension(boost::asio::io_service &io_service, avbot & mybot , std::string channel_name)
{
	mybot.on_message.connect(
		joke(io_service,
			io_service.wrap(boost::bind(sender, boost::ref(mybot), channel_name, _1, 0)),
			channel_name, boost::posix_time::seconds(600)
		)
	);

	mybot.on_message.connect(
		::urlpreview(io_service,
					io_service.wrap(boost::bind(sender, boost::ref(mybot), channel_name, _1, 1)),
					channel_name
		)
	);
#ifdef ENABLE_LUA
	mybot.on_message.connect(
		::callluascript(io_service,
					io_service.wrap(boost::bind(sender, boost::ref(mybot), channel_name, _1, 1)),
					channel_name
		)
	);
#endif
}
