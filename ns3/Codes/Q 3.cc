#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("starTopologyCW");

int main ()
{

	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  	NodeContainer starNodes;
  	starNodes.Create (5);

  	PointToPointHelper p2p;
  	p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  	p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

	NetDeviceContainer dv1;
  	dv1 = p2p.Install (starNodes.Get(0),starNodes.Get(1));
	
	NetDeviceContainer dv2;
  	dv2 = p2p.Install (starNodes.Get(0),starNodes.Get(2));

	NetDeviceContainer dv3;
  	dv3 = p2p.Install (starNodes.Get(0),starNodes.Get(3));
	
	NetDeviceContainer dv4;
  	dv4 = p2p.Install (starNodes.Get(0),starNodes.Get(4));

	InternetStackHelper stack;
  	stack.Install (starNodes);

  	Ipv4AddressHelper address;
  	address.SetBase ("10.1.1.0", "255.255.255.0");
  	Ipv4InterfaceContainer dv1Interfaces;
  	dv1Interfaces = address.Assign (dv1);

	address.SetBase ("10.1.2.0", "255.255.255.0");
  	Ipv4InterfaceContainer dv2Interfaces;
  	dv2Interfaces = address.Assign (dv2);

	address.SetBase ("10.1.3.0", "255.255.255.0");
  	Ipv4InterfaceContainer dv3Interfaces;
  	dv3Interfaces = address.Assign (dv3);

	address.SetBase ("10.1.4.0", "255.255.255.0");
  	Ipv4InterfaceContainer dv4Interfaces;
  	dv4Interfaces = address.Assign (dv4);

  	UdpEchoServerHelper echoServer (10);

  	ApplicationContainer serverApps = echoServer.Install (starNodes.Get (1));
  	serverApps.Start (Seconds (1.0));
  	serverApps.Stop (Seconds (10.0));

  	UdpEchoClientHelper echoClient (dv1Interfaces.GetAddress (1), 10);
  	echoClient.SetAttribute ("MaxPackets", UintegerValue (2));
  	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  	ApplicationContainer clientApps = echoClient.Install (starNodes.Get (4));
  	clientApps.Start (Seconds (2.0));
  	clientApps.Stop (Seconds (10.0));

  	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  	AnimationInterface anim("abc2.xml");

	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
