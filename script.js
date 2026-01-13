let events = [];


function showPanel(panelId){
    document.querySelectorAll('.panel').forEach(p => p.style.display='none');
    document.getElementById(panelId).style.display='block';
}


function dateToInt(date){
    const [d,m,y] = date.split('-').map(Number);
    return y*10000 + m*100 + d;
}


function insertEvent(){
    const id = parseInt(document.getElementById('addID').value);
    const name = document.getElementById('addName').value;
    const loc = document.getElementById('addLocation').value;
    const date = document.getElementById('addDate').value;
    const seats = parseInt(document.getElementById('addSeats').value);

    if(!id || !name || !loc || !date || !seats){ alert("Fill all fields!"); return; }

    events.push({id,name,loc,date,seats});
    events.sort((a,b)=>dateToInt(a.date)-dateToInt(b.date));
    displayEvents(true);
}


function modifyEvent(){
    const id = parseInt(document.getElementById('modifyID').value);
    const event = events.find(e=>e.id===id);
    if(!event){ alert("Event not found!"); return; }

    const name = document.getElementById('modifyName').value;
    const loc = document.getElementById('modifyLocation').value;
    const date = document.getElementById('modifyDate').value;
    const seats = parseInt(document.getElementById('modifySeats').value);

    if(name) event.name = name;
    if(loc) event.loc = loc;
    if(date) event.date = date;
    if(seats) event.seats = seats;

    events.sort((a,b)=>dateToInt(a.date)-dateToInt(b.date));
    displayEvents(true);
}

function deleteEvent(){
    const id = parseInt(document.getElementById('deleteID')?.value || document.getElementById('addID')?.value);
    const idx = events.findIndex(e=>e.id===id);
    if(idx===-1){ alert("Event not found!"); return; }
    events.splice(idx,1);
    displayEvents(true);
}


function searchEvent(){
    const id = parseInt(document.getElementById('searchID')?.value || document.getElementById('addID')?.value);
    const event = events.find(e=>e.id===id);
    if(!event){ alert("Event not found!"); return; }

    let html = `<h3>Event Found:</h3>
        <table>
        <tr><th>ID</th><th>Name</th><th>Location</th><th>Date</th><th>Seats</th></tr>
        <tr><td>${event.id}</td><td>${event.name}</td><td>${event.loc}</td><td>${event.date}</td><td>${event.seats}</td></tr>
        </table>`;
    document.getElementById('eventTable').innerHTML = html;
}


function displayEvents(forward=true){
    let arr = forward ? events : [...events].reverse();
    if(arr.length===0){ document.getElementById('eventTable').innerHTML="<p>No events available!</p>"; return; }

    let html = `<table>
        <tr><th>ID</th><th>Name</th><th>Location</th><th>Date</th><th>Seats</th></tr>`;
    arr.forEach(e=>{
        html += `<tr><td>${e.id}</td><td>${e.name}</td><td>${e.loc}</td><td>${e.date}</td><td>${e.seats}</td></tr>`;
    });
    html += `</table>`;
    document.getElementById('eventTable').innerHTML = html;
}
