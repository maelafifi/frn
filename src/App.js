import React, { Component } from 'react';
import logo from './frn2.jpg';
import logo2 from './USF_logo_green.jpg';
import filler from './filler.jpg'
import './App.css';
import About from './About';
import Events from './Events';
import Form from './Form';
import 'react-tabs/style/react-tabs.css';
import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';


class App extends Component {
  render() { 
    return (
      <div className="App">
      <button type="submit" class="myButton"> </button>
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo"/>
          <img src={filler} className="filler" alt="filler"/>
          <img src={logo2} className="App-logo" alt="logo2"/>
        </div>

    <Tabs>
    <TabList>
      <Tab>Report Food</Tab>
      <Tab> FRN Events </Tab>
      <Tab>About Us</Tab>
    </TabList>

    <TabPanel>
      <Form />
    </TabPanel>
    <TabPanel>
      <Events />
    </TabPanel>
    <TabPanel>
      <About />
    </TabPanel>
  </Tabs>

      </div>
    );
  }
}
export default App;
