#include <cstdint>
#include <cstdarg>
#include <iostream>

#include "options.hpp"

/* for ip conversions */
#include <arpa/inet.h>

/* mylog */
// #include <mylog/mylog.hpp>
#include <mylog/mylog.h>

/* libtins */
#include "tins/tcp_ip/stream_follower.h"
#include "tins/sniffer.h"
#include "tins/packet.h"
#include "tins/rawpdu.h"
#include "tins/ip.h"
#include "tins/dns.h"
#include "tins/tcp.h"
#include "tins/udp.h"
#include "tins/ip_address.h"
#include "tins/ipv6_address.h"
#include "tins/memory_helpers.h"
#include "tins/network_interface.h"

/* project includes */
#include "debug.h"
#include "include/tins_utils.hpp"
#include "dissect.hpp"

using Tins::Sniffer;
using Tins::SnifferConfiguration;
using Tins::PDU;
using Tins::IP;
using Tins::UDP;
using Tins::DNS;
using Tins::RawPDU;

/* tins_utils - global list */
extern std::unique_ptr<TU::IfaceInfo> ifinfo;

bool udp_dumper(const PDU& pdu) {
    /* The packet probably looks likes:
     *               EthernetII / IP / UDP / RawPDU
     * So retrieve the RawPDU layer + construct a DNS PDU using its contents: */
    // DNS dns = pdu.rfind_pdu<RawPDU>().to<DNS>();
    const RawPDU& raw = pdu.rfind_pdu<RawPDU>();
    // Finally, take the payload (this is a vector<uint8_t>)
    const RawPDU::payload_type& payload = raw.payload();
    // print_readable( (uint8_t*) payload.data(), payload.size() );
    std::cout << "[" << payload.size() << "]" << payload.data() << std::endl;

    return true;
}

int dissect(const char* iface)
{
    try {
        SnifferConfiguration c1;

        c1.set_immediate_mode(true);
        c1.set_promisc_mode(true);
        c1.set_filter("udp and dst port 1234");
        Sniffer s1( iface , c1);
        // s1.set_extract_raw_pdus(true);

        /* Capture. Every time there's a new packet.. */
        s1.sniff_loop([&](PDU& pdu) {
            if ( pdu.find_pdu<UDP>() ) {
                udp_dumper(pdu); // dns otherwise
            }
            return true;
        });
    } catch (std::exception& ex) {
        logerror("Error: %s", ex.what() );
    }

    /* end of main() */
}

bool validate_iface(std::string& check_if) {
    if ( TU::ifinfo->valid_name(check_if) )
        return true;
    logwarn("invalid interface \"%s\"\n", check_if.c_str() );
    TU::ifinfo->dump_shortlist();
    return false;
}

void dissect_help(void) {
    TU::ifinfo->dump_shortlist();
}
