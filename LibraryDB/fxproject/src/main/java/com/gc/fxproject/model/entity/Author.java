package com.gc.fxproject.model.entity;

public class Author {
    
    private int id;
    private String firstName;
    private String midName;
    private String lastName;
    private String dateBirth;
    private String dateDeath;
    
    public Author(int id, String firstName, String midName, String lastName, String dateBirth, String dateDeath) {
        this.id = id;
        this.firstName = firstName;
        this.midName = midName;
        this.lastName = lastName;
        this.dateBirth = dateBirth;
        this.dateDeath = dateDeath;
    }
    
    public int getId() {
        return id;
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
    
    public String getDateBirth() {
        return dateBirth;
    }
    
    public void setDateBirth(String dateBirth) {
        this.dateBirth = dateBirth;
    }
    
    public String getDateDeath() {
        return dateDeath;
    }
    
    public void setDateDeath(String dateDeath) {
        this.dateDeath = dateDeath;
    }
}
