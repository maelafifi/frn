import React, { Component } from 'react';
import './Form.css'; 

class About extends Component {
  

  render () {
    return (
      <form className="demoForm">
        <div class="headerfont">
          <h2>About Food Recovery Network</h2>

          Food Recovery Network is the largest student movement against food waste and hunger in America. <br/> <br/>
          In 2011, Ben Simon, Mia Zavalij and Cam Pascual, students at the University of Maryland, College Park noticed good dining hall food ending up in the trash at the end of the night. By the end of the school year, FRN at UMD had recovered 30,000 meals to DC-area hunger-fighting nonprofits.<br/><br/>
          During the Spring 2012 semester, the second FRN chapter was founded at Brown University, and the two schools joined forces with two other campus food recovery programs at University of California, Berkeley and Pomona College. <br/><br/>
          In May 2013, the Sodexo Foundation provided FRN with founding funding to hire a full-time staff and transition into a professional nonprofit! Since then, we've swept the nation and made higher education the first sector where food recovery is the norm and not the exception.<br/><br/>
          Find out more about our chapters here.<br/>
          <h2>University of San Francisco Chapter</h2>
          <a href = "https://docs.google.com/spreadsheets/d/1E12pRo4dxAf72Um0w5970DQbwiVcEyXJh1ea11sS0JQ/edit#gid=602549049"> Pounds to Date </a>
          <br/><br/>
        </div>
      </form>
    )
  }
}

export default About;