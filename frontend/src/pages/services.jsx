import React, { Component } from "react";
import Navigation from "../Components/Navigation";
import ServiceCard from "../Components/ServiceCard";

class services extends Component {

  render() {
    return (
      <div>
        <Navigation />
        <h1>Select which service to use:</h1>
        <ServiceCard></ServiceCard>
      </div>
    );
  }
}

export default services;
