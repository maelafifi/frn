import React, { Component } from 'react';
import { FormErrors } from './FormErrors';
import './Form.css'; 
import Form2 from './Form.js';
import Form3 from './Form.js';
import Form4 from './Form.js';

class Form extends Component {
  constructor (props) {
    super(props);
    this.state = {
      name:'',
      email: '',
      phone: '',
      date: '',
      time: '',
      building: '',
      formErrors: {name: '', email: '', phone: '', date: '', time: '', building: ''},
      nameValid: false,
      emailValid: false,
      phoneValid: false,
      dateValid: false,
      timeValid: false,
      buildingValid: false,
      formValid: false
    }
  }

  handleUserInput = (e) => {
    const name = e.target.name;
    const value = e.target.value;
    this.setState({[name]: value},
                  () => { this.validateField(name, value) });
  }

  validateField(fieldName, value) {
    let fieldValidationErrors = this.state.formErrors;
    let nameValid = this.state.nameValid;
    let emailValid = this.state.emailValid;
    let phoneValid = this.state.phoneValid;
    let dateValid = this.state.dateValid;
    let timeValid = this.state.timeValid;
    let buildingValid = this.state.buildingValid;

    switch(fieldName) {
      case 'email':
        emailValid = value.match(/^([\w.%+-]+)@([\w-]+\.)+([\w]{2,})$/i);
        fieldValidationErrors.email = emailValid ? '' : ' is invalid';
        break;
      case 'name':
        nameValid = value.length >= 2;
        fieldValidationErrors.name = nameValid ? '': ' is too short';
        break;
      case 'phone':
        phoneValid = value.length === 10;
        fieldValidationErrors.phone = phoneValid ? '': ' please enter only 10 numbers, without special characters';
        break;
      case 'date':
        dateValid = value.length === 10;
        fieldValidationErrors.date = dateValid ? '': ' Please enter MM/DD/YYYY format';
        break;
      case 'time':
        timeValid = true;
        break;
      case 'building':
        buildingValid = value.length >= 4;
        fieldValidationErrors.building = buildingValid ? '': 'Building name too short; please reenter';
        break;
      default:
        break;
    }
    this.setState({formErrors: fieldValidationErrors,
                    nameValid: nameValid,
                    emailValid: emailValid,
                    phoneValid: phoneValid,
                    dateValid: dateValid,
                    timeValid: timeValid,
                    buildingValid: buildingValid
                  }, this.validateForm);
  }

  validateForm() {
    this.setState({formValid: this.state.nameValid && this.state.emailValid && this.state.phoneValid &&
      this.state.dateValid && this.state.timeValid && this.state.buildingValid});
  }

  errorClass(error) {
    return(error.length === 0 ? '' : 'has-error');
  }

  render () {
    return (
      <form className="demoForm">
        <div class="headerfont">
          <h4>Enter Information For Food Pickup</h4>
        </div>
        <div className="panel panel-default">
          <FormErrors formErrors={this.state.formErrors} />
        </div>
        <div className={`form-group ${this.errorClass(this.state.formErrors.name)}`} class="specialfont">
          <label htmlFor="name">Name</label>
          <input type="name" required className="form-control" name="name"
            placeholder="Name"
            value={this.state.name}
            onChange={this.handleUserInput}  />
        </div>
        <div className={`form-group ${this.errorClass(this.state.formErrors.email)}`} class="specialfont">
          <label htmlFor="email">Email</label>
          <input type="email" className="form-control" name="email"
            placeholder="Email"
            value={this.state.email}
            onChange={this.handleUserInput}  />
        </div>
        <div className={`form-group ${this.errorClass(this.state.formErrors.phone)}`} class="specialfont">
          <label htmlFor="phone">Phone Number</label>
          <input type="phone" required className="form-control" name="phone"
            placeholder="Phone"
            value={this.state.phone}
            onChange={this.handleUserInput}  />
        </div>
        <div className={`form-group ${this.errorClass(this.state.formErrors.date)}`} class="specialfont">
          <label htmlFor="date">Date</label>
          <input type="date" className="form-control" name="date"
            placeholder="Date"
            value={this.state.date}
            onChange={this.handleUserInput}  />
        </div>
        <div className={`form-group ${this.errorClass(this.state.formErrors.time)}`} class="specialfont">
          <label htmlFor="time">Time</label>
          <input type="time" required className="form-control" name="time"
            placeholder="Time"
            value={this.state.time}
            onChange={this.handleUserInput}  />
        </div>
        <div className={`form-group ${this.errorClass(this.state.formErrors.building)}`} class="specialfont">
          <label htmlFor="building">Building</label>
          <input type="building" className="form-control" name="building"
            placeholder="Building"
            value={this.state.building}
            onChange={this.handleUserInput}  />
        </div>

        <button type="submit" class="submitbutton" disabled={!this.state.formValid}>Submit</button>

        <div class="navpane" id="mynav">
          <a href="Form">Report<br />Food</a>
          <a href= "Form2">FRN<br />Events</a>
          <a href="Form3">About<br />Us</a>
        </div>
      </form>
    )
  }
}

export default Form;