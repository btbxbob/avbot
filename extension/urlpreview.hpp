
#pragma once

#include <algorithm>
#include <boost/locale.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <avhttp.hpp>

class urlpreview
{
	boost::asio::io_service &io_service;
	boost::function<void ( std::string ) > m_sender;
	std::string m_channel_name;

public:
	template<class MsgSender>
	urlpreview( boost::asio::io_service &_io_service,  MsgSender sender, std::string channel_name )
		: io_service( _io_service ), m_sender( sender ), m_channel_name( channel_name )
	{
	}

	// on_message 回调.
	void operator()( boost::property_tree::ptree message ) const;
};
