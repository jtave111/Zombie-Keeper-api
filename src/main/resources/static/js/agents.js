const agentsBodyTable = document.getElementById("agents-body");

const endpoint = '/c2-server/agents';


async function loadAgents() {
    
const response = await fetch(endpoint); 

const data = await response.json();

    try {

        const response = await fetch(endpoint, {
            credentials: 'same-origin'
        });


        if(!response.ok){

            console.error("Endpoint refused")

            return;
        }
        
        data.forEach(agent => {
    
            const tr = document.createElement("tr");

            tr.innerHTML = ` 

                <td>${agent.hostname}</td>
                <td>${agent.os}</td>
                <td>${agent.ip}</td>
                <td>${agent.status}</td>
                <td>${agent.lastSeen}}</td>    
            `;

            agentsBodyTable.appendChild(tr);
            
        });

    } catch (error) {
        
        
        console.error("Endpoint fatal error", e);

    }

  

}
  loadAgents();