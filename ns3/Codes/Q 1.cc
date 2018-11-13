#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PointToPoint");

int main ()
{

	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  	NodeContainer p2pNodes;
  	p2pNodes.Create (2);

  	PointToPointHelper p2p;
  	p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  	p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

	NetDeviceContainer dv1;
  	dv1 = p2p.Install (p2pNodes.Get(0),p2pNodes.Get(1));

	InternetStackHelper stack;
  	stack.Install (p2pNodes);

  	Ipv4AddressHelper address;
  	address.SetBase ("10.1.1.0", "255.255.255.0");
  	Ipv4InterfaceContainer dv1Interfaces;
  	dv1Interfaces = address.Assign (dv1);

  	UdpEchoServerHelper echoServer (10);

  	ApplicationContainer serverApps = echoServer.Install (p2pNodes.Get (1));
  	serverApps.Start (Seconds (1.0));
  	serverApps.Stop (Seconds (10.0));

  	UdpEchoClientHelper echoClient (dv1Interfaces.GetAddress (1), 10);
  	echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  	ApplicationContainer clientApps = echoClient.Install (p2pNodes.Get (0));
  	clientApps.Start (Seconds (2.0));
  	clientApps.Stop (Seconds (10.0));

  	//Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  	AnimationInterface anim("abc3.xml");

	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
