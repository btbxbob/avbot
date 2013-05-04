
#pragma once

#include <algorithm>
#include <boost/locale.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

extern "C"{
#include <luajit-2.0/luajit.h>
#include <luajit-2.0/lualib.h>
#include <luajit-2.0/lauxlib.h>
}

class callluascript
{
	boost::asio::io_service &io_service;
	boost::function<void ( std::string ) > m_sender;
	std::string m_channel_name;
	mutable boost::shared_ptr<lua_State> m_lua_State;

	void load_lua() const;
	void call_lua(std::string jsondata) const ;

public:
	callluascript( boost::asio::io_service &_io_service,  boost::function<void ( std::string ) >  sender, std::string channel_name );
	~callluascript();
	// on_message 回调.
	void operator()( boost::property_tree::ptree message ) const;
};
