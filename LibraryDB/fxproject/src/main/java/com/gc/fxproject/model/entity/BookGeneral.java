package com.gc.fxproject.model.entity;

import java.sql.Date;

public class BookGeneral {
    
    private int id;
    private String title;
    private String udc;
    private Date dateDelivery;
    
    public BookGeneral(int id, String title, String udc, Date dateDelivety) {
        this.id = id;
        this.title = title;
        this.udc = udc;
        this.dateDelivery = dateDelivety;
    }
    
    public int getId() {
        return id;
    }
    
    public String getTitle() {
        return title;
    }
    
    public void setTitle(String title) {
        this.title = title;
    }
    
    public String getUdc() {
        return udc;
    }
    
    public void setUdc(String udc) {
        this.udc = udc;
    }
    
    public Date getDateDelivery() {
        return dateDelivery;
    }
    
    public void setDateDelivery(Date dateDelivery) {
        this.dateDelivery = dateDelivery;
    }
}
