import React, { Component } from 'react';
import logo from './USF_logo_green.jpg';
import logo2 from './frn2.jpg';
import './App.css';
import Form from './Form.js';

class App extends Component {
  render() { 
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo"/>
          <img src={logo2} className="App-logo" alt="logo2"/>
        </div>
        <Form />
      </div>
    );
  }
}
export default App;