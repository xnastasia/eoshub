import React, { Component } from "react";
import { Link } from "react-router-dom";
import Navigation from "../Components/Navigation";

import Image from "../img/logo.png";
import categories from "../img/categories.png";

class Homepage extends Component {
  render() {
    return (
      <div>
        <Navigation />
        <div class="services">
          <h1>Explore Services</h1>
          <div class="service">
            <Link to="/developers">
              <img src={categories} />
            </Link>
          </div>
        </div>
      </div>
    );
  }
}

export default Homepage;
