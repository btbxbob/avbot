
extern "C" {
#include <luajit-2.0/luajit.h>
#include <luajit-2.0/lualib.h>
#include <luajit-2.0/lauxlib.h>
}

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#include <boost/property_tree/json_parser.hpp>

#include "luabind/object.hpp"
#include "luabind/luabind.hpp"
#include "luabind/tag_function.hpp"
#include "luabind/function.hpp"

#include "luascript.hpp"

struct lua_sender
{
	boost::function<void ( std::string ) > m_sender;

	template<class F>
	lua_sender( F f ): m_sender( f ) {}

	void operator()( const char * str ) const
	{
		m_sender( str );
	}
};

callluascript::callluascript( boost::asio::io_service &_io_service,  boost::function<void ( std::string ) >  sender, std::string channel_name )
	: io_service( _io_service ), m_sender( sender ), m_channel_name( channel_name )
{
}

callluascript::~callluascript()
{

}

void callluascript::load_lua() const
{
	fs::path luafile;
	char *old_pwd = getenv( "O_PWD" );

	if( old_pwd )
	{
		luafile = fs::path( old_pwd ) /  "main.lua" ;
	}
	else
	{
		luafile = fs::current_path() / "main.lua" ;
	}

	// 实时载入, 修改后就马上生效!
	if( fs::exists( luafile ) )
	{
		lua_State* L = luaL_newstate();
		m_lua_State.reset( L, lua_close );
		luaL_openlibs( L );

		luabind::open( L );

		// 准备调用 LUA 脚本.
		luabind::module( L )[
			luabind::def( "send_channel_message", luabind::tag_function<void( const char * )>( lua_sender( m_sender ) ) )
		];

		luaL_dofile( L, luafile.c_str() );
	}
}

void callluascript::call_lua( std::string jsondata ) const
{
	lua_State* L = m_lua_State.get();

	if( L )
	{
		luabind::call_function<void>( L, "channel_message", jsondata);
	}
}

void callluascript::operator()( boost::property_tree::ptree message ) const
{
	if( message.get<std::string>( "channel" ) != m_channel_name )
	{
		return;
	}

	load_lua();
	std::stringstream jsondata;
	boost::property_tree::json_parser::write_json(jsondata, message);

	call_lua(jsondata.str());
}
