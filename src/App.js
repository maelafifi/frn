import React, { Component } from 'react';
import logo from './frn2.jpg';
import logo2 from './USF_logo_green.jpg';
import filler from './filler.jpg'
import './App.css';
import About from './About';
import Form from './Form';
import { BrowserRouter as Router, Route, Link } from 'react-router-dom'


class App extends Component {
  render() { 
    return (
      <div className="App">
      <button type="submit" class="Adminfont">Admin Page</button>
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo"/>
          <img src={filler} className="filler" alt="filler"/>
          <img src={logo2} className="App-logo" alt="logo2"/>
        </div>

        <Router>
         <div class="navpane" id="mynav">
          <a href="Form">Report<br />Food</a>
          <a href= "About">FRN<br />Events</a>
          <a href="About">About<br />Us</a>

      <hr/>

      <Route path="/Form" component={Form}/>
      <Route path="/about" component={About}/>
      <Route path="/topics" component={About}/>
    </div>
  </Router>
      </div>
    );
  }
}
export default App;