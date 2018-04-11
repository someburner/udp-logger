#ifndef TINSUTILS__h
#define TINSUTILS__h
// #include <uuid.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/uuid/uuid_generators.hpp> // generators
#include <sstream>
#include <mutex>

/* TU - TinsUtils */
namespace TU
{

using namespace Tins;

typedef struct {
    std::string name;
    std::string ip;
    std::string mac;
    bool up;
} BasicInfo_t;

class IfaceInfo {
public:
    IfaceInfo() {
        // std::cout << "Populating if info.." << std::endl;
        for (const NetworkInterface& iface : NetworkInterface::all()) {
            std::string name = iface.name();
            bool updown = iface.is_up();
            NetworkInterface::Info info = iface.info();
            // BasicInfo_t {name, ip, mac, up}
            _cur.push_back( {name, info.ip_addr.to_string(), info.hw_addr.to_string(), updown} );
        }
    }
    ~IfaceInfo() {}

    bool valid_name(std::string check_name) {
        for (auto const& it: _cur) {
            if (it.name.compare(check_name) == 0) return true;
        }
        return false;
    }

    void dump_shortlist(void) {
        for (auto const& it: _cur) {
            c_paintf_bri_ylw("%15s", it.name.c_str() );
            printf(" <"); c_paintf_wht("%s", it.mac.c_str() ); printf(">  ");
            if (it.up) { c_paintf_bri_grn("up"); }
            else { c_paintf_bri_red("down"); }
            printf("\n");
        }
        printf("\n\n");
    }

private:
    std::vector<BasicInfo_t> _cur;
};

std::unique_ptr<TU::IfaceInfo> ifinfo = std::make_unique<TU::IfaceInfo>();

inline void dump_if_list(void) {
    for (const NetworkInterface& iface : NetworkInterface::all()) {
        std::string name = iface.name();
        std::string status = iface.is_up() ? "up" : "down";
        NetworkInterface::Info info = iface.info();
        std::cout << name << ": " << std::endl;

        std::string ipv6_string;
        if (info.ipv6_addrs.empty()) {
            ipv6_string = "(none)";
        } else {
            std::ostringstream oss;
            for (size_t i = 0; i < info.ipv6_addrs.size(); ++i) {
                const NetworkInterface::IPv6Prefix& prefix = info.ipv6_addrs[i];
                if (i > 0) {
                    oss << ", ";
                }
                oss << prefix.address << "/" << prefix.prefix_length;
            }
            ipv6_string = oss.str();
        }
        std::cout   << "   HW address:     " << info.hw_addr << std::endl
                    << "   IP address:     " << info.ip_addr <<  std::endl
                    << "   IPv6 addresses: " << ipv6_string <<  std::endl
                    << "   Netmask:        " << info.netmask <<  std::endl
                    << "   Broadcast:      " << info.bcast_addr <<  std::endl
                    << "   Iface index:    " << iface.id() <<  std::endl
                    << "   Status:         interface " << status << "\n\n";
    }
    // auto *hw = new HWAddress<6>("s5k6sryk");
    // if (hw) std::cout << "success\n";
}

inline std::string dump_pdu_type(PDU::PDUType type) {
    switch (type) {
        case PDU::ETHERNET_II: return "Ethernet_II";
        case PDU::DOT3: return "IEEE_802.3";
        case PDU::DOT11: return "IEEE_802.11";
        case PDU::TCP: return "TCP";
        case PDU::IP: return "IPv4";
        case PDU::ARP: return "ARP";
        case PDU::ICMP: return "ICMP";
        case PDU::DNS: return "DNS";
        case PDU::UDP: return "UDP";
        case PDU::DHCP: return "DHCP";
        case PDU::LOOPBACK: return "LOOPBACK";
        case PDU::SNAP: return "SNAP";
        case PDU::LLC: return "LLC";
        case PDU::IPv6: return "IPv6";
        case PDU::STP: return "STP";
    }
    return "UNKNOWN - " + std::to_string(type);
}

} /* TU */


#endif /* TINSUTILS__h */
