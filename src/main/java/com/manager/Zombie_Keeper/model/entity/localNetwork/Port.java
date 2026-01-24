package com.manager.Zombie_Keeper.model.entity.localNetwork;

import com.fasterxml.jackson.annotation.JsonIgnore;

import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;

@Entity
@Table(name = "tb_node_ports")
public class Port {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    Long id;
    
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "node_id")
    @JsonIgnore
    NetworkNode node;

    private int number;
    private String protocol;
    private String service;
    private String banner;

    public Port(int number, String protocol, String service, String banner) {
        this.number = number;
        this.protocol = protocol;
        this.service = service;
        this.banner = banner;
    }


    public Port(){

        
    }


    public NetworkNode getNode(){

        return this.node;
    }

    public void setNode(NetworkNode node){
        
        this.node = node;
    }

    public int getNumber() {
        return this.number;
    }


    public void setNumber(int number) {
        this.number = number;
    }


    public String getProtocol() {
        return this.protocol;
    }


    public void setProtocol(String protocol) {
        this.protocol = protocol;
    }


    public String getService() {
        return this.service;
    }


    public void setService(String service) {
        this.service = service;
    }


    public String getBanner() {
        return this.banner;
    }


    public void setBanner(String banner) {
        this.banner = banner;
    }



}
