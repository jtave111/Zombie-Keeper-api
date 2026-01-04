package com.manager.Zombie_Keeper.service.shellExecutorService.scanners;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.concurrent.TimeUnit;

import org.springframework.boot.system.ApplicationHome;
import org.springframework.stereotype.Service;

@Service
public class ScannersExecService {


    public File getRootPath(){

        return new ApplicationHome(getClass()).getDir();
        
    }

    public String execScannLocalIps(String binaryName){

        StringBuilder output = new StringBuilder();

        try {

            File root = getRootPath();          
            File binaryFile = new File(root, "modules/linx/elf" + binaryName );

            if(!binaryFile.exists()){

                return "ERRO fileNotFund " + binaryFile.getAbsolutePath();

            }

            if(!binaryFile.canExecute()){
                binaryFile.setExecutable(true);
            }



            ProcessBuilder pb = new ProcessBuilder();

            pb.command(binaryFile.getAbsolutePath());
            pb.redirectErrorStream(true);


            Process process = pb.start();
            

            try (BufferedReader buffer = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                
                String line;

                while ((line = buffer.readLine())  != null) {
                    output.append(line).append("\n");
                }
            } 

            boolean finished = process.waitFor(60, TimeUnit.SECONDS);

            if(!finished){
                process.destroyForcibly();
                output.append("\nERROR");
            }
            
        } catch (Exception e) {

            e.printStackTrace();

            System.out.println("Catch ERROR " +  e.getMessage());

        }


        return output.toString();
    }

    
}
