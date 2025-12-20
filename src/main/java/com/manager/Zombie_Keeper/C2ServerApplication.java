package com.manager.Zombie_Keeper;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import com.manager.Zombie_Keeper.model.User;
import com.manager.Zombie_Keeper.service.AuthService;


@SpringBootApplication
public class C2ServerApplication  {

	public static void main(String[] args) {
		SpringApplication.run(C2ServerApplication.class, args);


	}


	

}
