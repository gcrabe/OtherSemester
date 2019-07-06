package com.gc.fxproject.model.entity;

public class BookEdition {
    
    private int id;
    private PublishingHouse publishingHouse;
    private BookGeneral bookGeneral;
    private int editionYear;
    private int countPages;
    private boolean isIllustrated;
    private String isbn;
    private String lbc;
    private boolean isOriginal;
    private int countExemplars;
    private int countAvailable;
    
    public BookEdition(int id, PublishingHouse publishingHouse, BookGeneral bookGeneral,
                        int editionYear, int countPages, boolean isIllustrated, String isbn,
                        String lbc, boolean isOriginal, int countExemplars, int countAvailable) {
        this.id = id;
        this.publishingHouse = publishingHouse;
        this.bookGeneral = bookGeneral;
        this.editionYear = editionYear;
        this.countPages = countPages;
        this.isIllustrated = isIllustrated;
        this.isbn = isbn;
        this.lbc = lbc;
        this.isOriginal = isOriginal;
        this.countExemplars = countExemplars;
        this.countAvailable = countAvailable;
    }
    
    public int getId() {
        return id;
    }
    
    public PublishingHouse getPublishingHouse() {
        return publishingHouse;
    }
    
    public void setPublishingHouse(PublishingHouse publishingHouse) {
        this.publishingHouse = publishingHouse;
    }
    
    public BookGeneral getBookGeneral() {
        return bookGeneral;
    }
    
    public void setBookGeneral(BookGeneral bookGeneral) {
        this.bookGeneral = bookGeneral;
    }
    
    public int getEditionYear() {
        return editionYear;
    }
    
    public void setEditionYear(int editionYear) {
        this.editionYear = editionYear;
    }
    
    public int getCountPages() {
        return countPages;
    }
    
    public void setCountPages(int countPages) {
        this.countPages = countPages;
    }
    
    public boolean getIsIllustrated() {
        return isIllustrated;
    }
    
    public void setIsIllustrated(boolean isIllustrated) {
        this.isIllustrated = isIllustrated;
    }
    
    public String getIsbn() {
        return isbn;
    }
    
    public void setIsbn(String isbn) {
        this.isbn = isbn;
    }
    
    public String getLbc() {
        return lbc;
    }
    
    public void setLbc(String lbc) {
        this.lbc = lbc;
    }
    
    public boolean getIsOriginal() {
        return isOriginal;
    }
    
    public void setOriginal(boolean isOriginal) {
        this.isOriginal = isOriginal;
    }
    
    public int getCountExemplars() {
        return countExemplars;
    }
    
    public void setCountExemplars(int countExemplars) {
        this.countExemplars = countExemplars;
    }
    
    public int getCountAvailable() {
        return countAvailable;
    }
    
    public void setCountAvailable(int countAvailable) {
        this.countAvailable = countAvailable;
    }
}
