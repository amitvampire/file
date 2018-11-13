#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("meshTopologyCW");

int main ()
{

	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  	NodeContainer meshNodes;
  	meshNodes.Create (4);

  	PointToPointHelper p2p;
  	p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  	p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

	NetDeviceContainer dv1;
  	dv1 = p2p.Install (meshNodes.Get(0),meshNodes.Get(1));
	
	NetDeviceContainer dv2;
  	dv2 = p2p.Install (meshNodes.Get(1),meshNodes.Get(2));

	NetDeviceContainer dv3;
  	dv3 = p2p.Install (meshNodes.Get(2),meshNodes.Get(3));
	
	NetDeviceContainer dv4;
  	dv4 = p2p.Install (meshNodes.Get(0),meshNodes.Get(3));

	NetDeviceContainer dv5;
  	dv5 = p2p.Install (meshNodes.Get(0),meshNodes.Get(2));
	
	NetDeviceContainer dv6;
  	dv6 = p2p.Install (meshNodes.Get(1),meshNodes.Get(3));

	InternetStackHelper stack;
  	stack.Install (meshNodes);

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

	address.SetBase ("10.1.5.0", "255.255.255.0");
  	Ipv4InterfaceContainer dv5Interfaces;
  	dv5Interfaces = address.Assign (dv5);

	address.SetBase ("10.1.6.0", "255.255.255.0");
  	Ipv4InterfaceContainer dv6Interfaces;
  	dv6Interfaces = address.Assign (dv6);

  	UdpEchoServerHelper echoServer (10);

  	ApplicationContainer serverApps = echoServer.Install (meshNodes.Get (0));
  	serverApps.Start (Seconds (1.0));
  	serverApps.Stop (Seconds (10.0));

  	UdpEchoClientHelper echoClient (dv1Interfaces.GetAddress (0), 10);
  	echoClient.SetAttribute ("MaxPackets", UintegerValue (2));
  	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  	ApplicationContainer clientApps = echoClient.Install (meshNodes.Get (2));
  	clientApps.Start (Seconds (2.0));
  	clientApps.Stop (Seconds (10.0));

  	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  	//PointToPoint.EnablePcapAll ("second");
  	//csma.EnablePcap ("second", csmaDevices.Get (1), true);

  	AnimationInterface anim("abc2.xml");

	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
