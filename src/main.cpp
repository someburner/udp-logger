/* --- /precompiled --- */
// #include "include/stdafx.h"
#include <cstdint>
#include <iostream>
#include <unistd.h> // getuid

/* mylog */
#include <mylog/mylog.hpp>

/* project includes */
#include "options.hpp"
#include "debug.h"

/* project includes */
#include "dissect.hpp"

#include "include/clipp.h"
#include "include/version.hpp"

int main(int argc, char* argv[]) {
    try {
        MYLOG::active_logger = std::unique_ptr<MYLOG::logger>(new MYLOG::logger(MYLOG::logger::log_level::okay));
        if (getuid() != 0) {
            std::cout << "Must be root." << std::endl;
            exit(1);
        }
    } catch (std::exception& e) {
        std::cout << "Unable to init logging (" << e.what() << ")" << std::endl;
        exit(1);
    }

    bool print_version = false;
    bool daemonize = false;
    bool show_ifs = false;
    bool show_help = false;
    std::string iface = "invalid";
    std::string pidfile, logfile;

    auto cli = (
        clipp::option("-i", "--iface")  & clipp::value("interface", iface),
        clipp::option("-d", "--daemonize").set(daemonize).doc("run as daemon"),
        clipp::option("-l", "--logfile").set(logfile).doc("redirect logging"),
        clipp::option("-v", "--version").set(print_version).doc("print version and exit"),
        clipp::option("-p", "--pidfile") & clipp::value("pid file location (daemon)", pidfile),
        clipp::option("-h", "--help").set(show_help).doc("Print help"),
        clipp::option("-s", "--show").set(show_ifs).doc("List available interfaces and exit")
    );

    if ( (argc < 2) || !clipp::parse(argc, argv, cli) ) {
        std::cout << make_man_page(cli, argv[0]);
        exit(1);
    }
    if (print_version) {
        std::cout << "Version: " << get_version() << "\n";
        std::cout << "   [ libpcap-" << get_pcap_version() << " ]\n";
        std::cout << "   [ libtins-" << get_tins_version() << " ]\n";
        exit(0);
    }
    if (show_help) { std::cout << make_man_page(cli, argv[0]) << "\n"; exit(0); }
    log("Logging init");
    log("Interface provided: %s", iface.c_str() );

    if (strstr("any", iface.c_str()) != NULL) {
        iface = "any";
    } else if ( !validate_iface(iface) ) {
        exit(1);
    }

    try {
        log("dissect begin..");
        int ret = dissect( iface.c_str() );
    }
    catch (std::exception& ex) {
        logerror("Error: %s", ex.what() );
    }
}













/* EOF */
