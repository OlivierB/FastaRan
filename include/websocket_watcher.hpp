#ifndef WEBSCOKETWATCHER_H
#define WEBSCOKETWATCHER_H

#include <iostream>
#include <thread>

#define _WEBSOCKETPP_CPP11_THREAD_
#define _WEBSOCKETPP_CPP11_FUNCTIONAL_
#define _WEBSOCKETPP_CPP11_SYSTEM_ERROR_
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_MEMORY_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "fasta_creator.hpp"

typedef websocketpp::server<websocketpp::config::asio> server;
// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class WebSocketWatcher{
	public:
		// Constructeurs
		WebSocketWatcher(FastaCreator *fastaCreator);
		~WebSocketWatcher();	

		void run(int port);
		void join();


		
	private:
		FastaCreator *ws_fastaCreator;	
		std::thread* t1;
		server print_server;
		double vm_usage;
		double resident_set;

		void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg);

		void call_from_thread();
    	double getMemUsage( const bool VM );
};


#endif
