import React, { Component } from "react";
import { Link } from "react-router-dom";

import Image from "../img/logo.png";

class Navigation extends Component {
  render() {
    return (
      <div class="navigation">
        <Link to="/">
          <img src={Image} />
        </Link>
        <div class="menu">
          <nav>
            <input type="text" placeholder="Search Services" />
            <span>
              <Link to="/services">Services</Link>
            </span>
            <span>
              <Link to="/developers">Developers</Link>
            </span>
          </nav>
        </div>
      </div>
    );
  }
}

export default Navigation;
