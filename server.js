const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000;


app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));


app.use(express.static(__dirname));


let events = [];

function dateToInt(date) {
    const [d, m, y] = date.split('-').map(Number);
    return y * 10000 + m * 100 + d;
}



app.post('/add', (req, res) => {
    const { id, name, loc, date, seats } = req.body;
    if (!id || !name || !loc || !date || !seats) return res.status(400).send({ error: 'Missing fields' });
    events.push({ id, name, loc, date, seats });
    events.sort((a, b) => dateToInt(a.date) - dateToInt(b.date));
    res.send({ message: 'Event added', events });
});

app.post('/modify', (req, res) => {
    const { id, name, loc, date, seats } = req.body;
    const event = events.find(e => e.id == id);
    if (!event) return res.status(404).send({ error: 'Event not found' });
    if (name) event.name = name;
    if (loc) event.loc = loc;
    if (date) event.date = date;
    if (seats) event.seats = seats;
    events.sort((a, b) => dateToInt(a.date) - dateToInt(b.date));
    res.send({ message: 'Event modified', events });
});


app.post('/delete', (req, res) => {
    const { id } = req.body;
    const index = events.findIndex(e => e.id == id);
    if (index === -1) return res.status(404).send({ error: 'Event not found' });
    events.splice(index, 1);
    res.send({ message: 'Event deleted', events });
});


app.get('/search/:id', (req, res) => {
    const id = parseInt(req.params.id);
    const event = events.find(e => e.id == id);
    if (!event) return res.status(404).send({ error: 'Event not found' });
    res.send({ event });
});


app.get('/display', (req, res) => {
    const { order } = req.query; // 'asc' or 'desc'
    let result = [...events];
    if (order === 'desc') result.reverse();
    res.send({ events: result });
});


app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});

