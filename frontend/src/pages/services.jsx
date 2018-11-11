import React, { Component } from "react";
import Navigation from "../Components/Navigation";
import ServiceCard from "../Components/ServiceCard";

import img from "../img/elasticsearch.jpg";
import security from "../img/sec.png";
import analy from "../img/analy.png";
import chat from "../img/chat.png";


class services extends Component {

  render() {
    return (
      <div>
        <Navigation />
        <h1>Select which service to use:</h1>
        <ServiceCard img={img} title={"Elastic dApp"} desc={"dApp leveraging Elastic Search to provide a seach engine for decentralized applications"}></ServiceCard>
        <ServiceCard img={security} title={"Security dApp"} desc={"provides a layer of security to verify tokens are valid"}></ServiceCard>
        <ServiceCard img={analy} title={"Analytics dApp"} desc={"Analytics for your dApp"}></ServiceCard>
        <ServiceCard img={chat} title={"Chat dApp"} desc={"dApp leveraging Elastic Search to provide a seach engine for decentralized applications"}></ServiceCard>
        <ServiceCard img={security} title={"Security dApp"} desc={"provides a layer of security to verify tokens are valid"}></ServiceCard>
        <ServiceCard img={analy} title={"Analytics dApp"} desc={"Analytics for your dApp"}></ServiceCard>
        <ServiceCard img={img} title={"Elastic dApp"} desc={"dApp leveraging Elastic Search to provide a seach engine for decentralized applications"}></ServiceCard>
        <ServiceCard img={chat} title={"Chat dApp"} desc={"provides a layer of security to verify tokens are valid"}></ServiceCard>
      </div>
    );
  }
}

export default services;
