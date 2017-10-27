import React, { Component } from 'react';
import logo from './frn2.jpg';
import logo2 from './USF_logo_green.jpg';
import filler from './filler.jpg'
import './App.css';
import About from './About';
import Form from './Form';
import { Tabs, TabLink, TabContent } from 'react-tabs-redux';


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

       <Tabs>
    <TabLink to="tab1">Submit Food</TabLink>
    <TabLink to="tab2">About Us</TabLink>
    <TabLink to="tab3">Events</TabLink>
 
    <TabContent for="tab1"><Form/></TabContent>
    <TabContent for="tab2"><About/></TabContent>
    <TabContent for="tab3"><Form/></TabContent>
</Tabs>
      </div>
    );
  }
}
export default App;