package com.manager.Zombie_Keeper.model.embeddable;

import jakarta.persistence.Embeddable;


@Embeddable
public class Ports {

    private int number;
    private String protocol;
    private String service;
    private String banner;

    public Ports(int number, String protocol, String service, String banner) {
        this.number = number;
        this.protocol = protocol;
        this.service = service;
        this.banner = banner;
    }


    public Ports(){

        
    }


    public int getNumber() {
        return number;
    }


    public void setNumber(int number) {
        this.number = number;
    }


    public String getProtocol() {
        return protocol;
    }


    public void setProtocol(String protocol) {
        this.protocol = protocol;
    }


    public String getService() {
        return service;
    }


    public void setService(String service) {
        this.service = service;
    }


    public String getBanner() {
        return banner;
    }


    public void setBanner(String banner) {
        this.banner = banner;
    }





}
