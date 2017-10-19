import React, { Component } from 'react';
import logo from './frn2.jpg';
import logo2 from './USF_logo_green.jpg';
import filler from './filler.jpg'
import './App.css';
import Form from './Form.js';

class App extends Component {
  render() { 
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo"/>
          <img src={filler} className="filler" alt="filler"/>
          <img src={logo2} className="App-logo" alt="logo2"/>
        </div>
        <Form />
      </div>
    );
  }
}
export default App;