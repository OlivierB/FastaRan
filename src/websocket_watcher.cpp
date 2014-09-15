  #include "../include/websocket_watcher.hpp"


  using namespace std;

  void WebSocketWatcher::on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
          std::cout << "Payload : " << endl << msg->get_payload() << " Code " << msg->get_opcode() << std::endl << flush;
          if(msg->get_payload() == "coverage")
          	print_server.send(hdl, std::to_string(ws_fastaCreator->get_coverage()), msg->get_opcode());
          else if(msg->get_payload() == "file_size")
          	print_server.send(hdl, std::to_string(ws_fastaCreator->get_file_size()), msg->get_opcode());
          else if(msg->get_payload().substr(0, 7) == "nucleos")
          	print_server.send(hdl,ws_fastaCreator->get_chaine(stoi(msg->get_payload().substr(8)), 2), msg->get_opcode());
          else if(msg->get_payload() == "sequences_cover")
          	print_server.send(hdl,ws_fastaCreator->get_coverage_json(), msg->get_opcode());
          else if(msg->get_payload() == "mem_usage")
          	print_server.send(hdl,std::to_string(getMemUsage(false)), msg->get_opcode());
          
  }

  void WebSocketWatcher::call_from_thread() {
      

      print_server.set_message_handler(bind(&WebSocketWatcher::on_message, this, ::_1, ::_2));
      print_server.set_reuse_addr(true);
      print_server.init_asio();
      print_server.listen(9002);
      print_server.start_accept();

      print_server.run();
  }

  WebSocketWatcher::WebSocketWatcher(FastaCreator *fastaCreator)
  {
  	ws_fastaCreator = fastaCreator;
  }

  WebSocketWatcher::~WebSocketWatcher()
  {
  }

  void WebSocketWatcher::run(int port)
  {
  	t1 = new thread(&WebSocketWatcher::call_from_thread, this);
  	
  }

  void WebSocketWatcher::join(){
  	print_server.stop_listening();
  	t1->join();
  }

  double WebSocketWatcher::getMemUsage( const bool VM )
  {
     using std::ios_base;
     using std::ifstream;
     using std::string;
     
     // 'file' stat seems to give the most reliable results
     //
     ifstream stat_stream("/proc/self/stat",ios_base::in);
     
     // dummy vars for leading entries in stat that we don't care about
     //
     string pid, comm, state, ppid, pgrp, session, tty_nr;
     string tpgid, flags, minflt, cminflt, majflt, cmajflt;
     string utime, stime, cutime, cstime, priority, nice;
     string O, itrealvalue, starttime;
     
     // the two fields we want
     //
     unsigned long vsize;
     long rss;
     
     stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                 >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                 >> utime >> stime >> cutime >> cstime >> priority >> nice
                 >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest
     
     stat_stream.close();
     
     if ( VM ) {
       double vm_usage = vsize / 1024.0; // this gives virtual memory usage
       return vm_usage;
     }
     
     else {
       long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
       double resident_set = rss * page_size_kb;
       return resident_set;
     }
  }