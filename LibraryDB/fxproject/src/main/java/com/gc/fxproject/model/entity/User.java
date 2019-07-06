package com.gc.fxproject.model.entity;

import java.sql.Date;

public class User {
    
    private int id;
    private String priority;
    private String login;
    private String password;
    private String firstName;
    private String midName;
    private String lastName;
    private Date dateBirth;
    private Department department;
    private String jobTitle;
    private Date dateRegistration;
    
    public User(int id, String priority, String login, String password, 
                String firstName, String midName, String lastName, Date dateBirth,
                Department department, String jobTitle, Date dateRegstration) {
        this.id = id;
        this.priority = priority;
        this.login = login;
        this.password = password;
        this.firstName = firstName;
        this.midName = midName;
        this.lastName = lastName;
        this.dateBirth = dateBirth;
        this.department = department;
        this.jobTitle = jobTitle;
        this.dateRegistration = dateRegstration;
    }
    
    public int getId() {
        return id;
    }
    
    public String getPriotiry() {
        return priority;
    }
    
    public void setPriority(String priority) {
        this.priority = priority;
    }
    
    public String getLogin() {
        return login;
    }
    
    public void setLogin(String login) {
        this.login = login;
    }
    
    public String getPassword() {
        return password;
    }
    
    public void setPassword(String password) {
        this.password = password;
    }
    
    public String getFirstName() {
        return firstName;
    }
    
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }
    
    public String getMidName() {
        return midName;
    }
    
    public void setMidName(String midName) {
        this.midName = midName;
    }
    
    public String getLastName() {
        return lastName;
    }
    
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }
    
    public Date getDateBirth() {
        return dateBirth;
    }
    
    public void setDateBirth(Date dateBirth) {
        this.dateBirth = dateBirth;
    }
    
    public Department getDepartment() {
        return department;
    }
    
    public void setDepartment(Department department) {
        this.department = department;
    }
    
    public String getJobTitle() {
        return jobTitle;
    }
    
    public  void setJobTitle(String jobTitle) {
        this.jobTitle = jobTitle;
    }
    
    public Date getDateRegistration() {
        return dateRegistration;
    }
    
    public void setDateRegistration(Date dateRegistration) {
        this.dateRegistration = dateRegistration;
    }
}
