package com.gc.fxproject.model.entity;

import java.sql.Date;

public class Action {
    
    private int id;
    private BookExemplar bookExemplar;
    private User user;
    private Date dateBorrowing;
    private Date dateRequired;
    private Date dateActual;
    
    public Action(int id, BookExemplar bookExemplar, User user, Date dateBorrowing,
                    Date dateRequired, Date dateActual) {
        this.id = id;
        this.bookExemplar = bookExemplar;
        this.user = user;
        this.dateBorrowing = dateBorrowing;
        this.dateRequired = dateRequired;
        this.dateActual = dateActual;
    }
    
    public int getId() {
        return id;
    }
    
    public BookExemplar getBookExemplar() {
        return bookExemplar;
    }
    
    public void setBookExemplar(BookExemplar bookExemplar) {
        this.bookExemplar = bookExemplar;
    }
    
    public User getUser() {
        return user;
    }
    
    public void setUser(User user) {
        this.user = user;
    }
    
    public Date getDateBorrowing() {
        return dateBorrowing;
    }
    
    public void setDateBorrowing(Date dateBorrowing) {
        this.dateBorrowing = dateBorrowing;
    }
    
    public Date getDateRequired() {
        return  dateRequired;
    }
    
    public void setDateRequired(Date dateRequired) {
        this.dateRequired = dateRequired;
    }
    
    public Date getDateActual() {
        return dateActual;
    }
    
    public void setDateActual(Date dateActual) {
        this.dateActual = dateActual;
    }
}
