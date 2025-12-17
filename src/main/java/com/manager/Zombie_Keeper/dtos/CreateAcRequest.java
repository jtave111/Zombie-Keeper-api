package com.manager.Zombie_Keeper.dtos;

import jakarta.validation.constraints.NotBlank;

public class CreateAcRequest {

   @NotBlank(message = "not balank field")
   private String Name;
   @NotBlank(message = "not balank field")
   private String username;
   @NotBlank(message = "not balank field")
   private String password;
   @NotBlank(message = "not balank field")
   private String role;


   public String getName() {
    return Name;
   }
   public void setName(String name) {
    Name = name;
   }
   public String getUsername() {
    return username;
   }
   public void setUsername(String username) {
    this.username = username;
   }
   public String getPassword() {
    return password;
   }
   public void setPassword(String password) {
    this.password = password;
   }
   public String getRole() {
    return role;
   }
   public void setRole(String role) {
    this.role = role;
   }

    

}
