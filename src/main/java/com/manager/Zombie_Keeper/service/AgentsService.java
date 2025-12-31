package com.manager.Zombie_Keeper.service;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.springframework.stereotype.Service;

import com.manager.Zombie_Keeper.model.Agent;
import com.manager.Zombie_Keeper.model.enums.Tags;
@Service
public class AgentsService {
  


    public Agent setPreInformation(Agent agent){
        
        Set<Tags> set = new HashSet<>();
        
        if(isWin(agent.getOs())){
            set.add(Tags.WINDOWS);

            agent.setTgas(set);
        }

        

        return agent;
    }



    public static Boolean isWin(String os){
        
        if (!os.contains("w") || !os.contains("i") || !os.contains("n")) {
            return false;
        }

        if(os.length() < 3) return false;

        os = os.toLowerCase().replaceAll("\\s", "");

        if(os.equalsIgnoreCase("windows")) return true;

        int pointer = 0, i= 0 , target = 0;
        char []  expected = {'w', 'i', 'n' };

        while (pointer < 3) if(os.charAt(pointer++) == expected[ i++]) target++;

        if(target == 3) return true;


        char[] arr = {'w', 'i', 'n', 'd',  'o', 'n', 'w', };

        Map<Integer, Boolean> map = new HashMap<>();

        int acept = 6, contArr = 0, aux = 0;

        for(int j = 0; j < os.length(); j ++){


            map.put(contArr, false);

            if(os.charAt(j) == arr[contArr] && (map.get(contArr) == false ) ){

                map.put(contArr, true);

                aux ++;

            }

            contArr ++;

            if(contArr >=  arr.length ) contArr = 0;

        }

        if(aux == acept -1) return true;

        return  false;
    }

    public static Boolean isLinux(String os) {
        os = os.toLowerCase().replaceAll("\\s", "");
        
        if (os.length() < 3) return false;

        if (!os.contains("l") || !os.contains("i") || !os.contains("n")) {
            return false;
        }

        if (os.contains("linux")) return true;

        int pointer = 0, i = 0, target = 0;
        char[] expected = {'l', 'i', 'n'}; 

        while (pointer < 3 && pointer < os.length()) {
            if (os.charAt(pointer++) == expected[i++]) target++;
        }
        
        if (target == 3) return true;

        char[] arr = {'l', 'i', 'n', 'u', 'x'};
        Map<Integer, Boolean> map = new HashMap<>();
        int acept = 4, contArr = 0, aux = 0;

        for (int j = 0; j < os.length(); j++) {
            map.put(contArr, false);
            if (os.charAt(j) == arr[contArr] && !map.get(contArr)) {
                map.put(contArr, true);
                aux++;
            }
            contArr++;
            if (contArr >= arr.length) contArr = 0;
        }

        return aux >= acept;
    }
 

    public static Boolean isMac(String os) {
        os = os.toLowerCase().replaceAll("\\s", "");
        
        if (os.length() < 3) return false;

        if (!os.contains("m") || !os.contains("a") || !os.contains("c")) {
            return false;
        }

        if (os.contains("macos") || os.contains("darwin")) return true;

        int pointer = 0, i = 0, target = 0;
        char[] expected = {'m', 'a', 'c'};

        while (pointer < 3 && pointer < os.length()) {
            if (os.charAt(pointer++) == expected[i++]) target++;
        }
        
        if (target == 3) return true;

        char[] arr = {'m', 'a', 'c', 'o', 's'};
        Map<Integer, Boolean> map = new HashMap<>();
        int acept = 3, contArr = 0, aux = 0;

        for (int j = 0; j < os.length(); j++) {
            map.put(contArr, false);
            if (os.charAt(j) == arr[contArr] && !map.get(contArr)) {
                map.put(contArr, true);
                aux++;
            }
            contArr++;
            if (contArr >= arr.length) contArr = 0;
        }

        return aux >= acept;
    }


}
