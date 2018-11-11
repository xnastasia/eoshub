import React, { Component } from "react";
import img from "../img/elasticsearch.jpg";

import "rc-slider/assets/index.css";
import Tooltip from "rc-tooltip";
import Slider from "rc-slider";

const createSliderWithTooltip = Slider.createSliderWithTooltip;
const Range = createSliderWithTooltip(Slider.Range);
const Handle = Slider.Handle;

// const handle = props => {
//   const { value, dragging, index, ...restProps } = props;
//   return (
//     <Tooltip
//       prefixCls="rc-slider-tooltip"
//       overlay={value}
//       visible={dragging}
//       placement="top"
//       key={index}
//     >
//       <Handle value={value} {...restProps} />
//     </Tooltip>
//   );
// };

class services extends Component {
  constructor() {
    super();
    this.state = {
      iniRequests: 50000,
      requests: 50000
    };
    this.setRequestsPerMinute = this.setRequestsPerMinute.bind(this);
    this.handle = this.handle.bind(this);
  }

  handle(props) {
    const { value, dragging, index, ...restProps } = props;
    if (this.state.requests != value) {
      this.setRequestsPerMinute(value);
    }
    return (
      <Tooltip
        prefixCls="rc-slider-tooltip"
        overlay={value}
        visible={dragging}
        placement="top"
        key={index}
      >
        <Handle value={value} {...restProps} />
      </Tooltip>
    );
  }

  setRequestsPerMinute(value) {
    this.setState({ requests: value });
  }
  render() {
    return (
      <div class="card">
        <img class="card-img-top" src={img} alt="Elastic Service" />
        <div class="card-body">
          <h5 class="card-title">Elastic dApp</h5>
          <p class="card-text">
            dApp leveraging Elastic Search to provide a seach engine for decentralized applications
          </p>
          <div class="slider">
            <p>Requests per Month: {this.state.requests}</p>
            <Slider
              min={1000}
              max={200000}
              defaultValue={this.state.iniRequests}
              handle={this.handle}
            />
          </div>
          <a id="elastic" class="btn btn-primary">
            Stack {parseFloat(this.state.requests * 0.000001).toFixed(4)} EOSHub tokens
          </a>
        </div>
      </div>
    );
  }
}

export default services;
