var express = require('express');
var router = express.Router();

var fs = require("fs");
var mysql = require('mysql');
var con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "mydb"
});
con.connect(function (err) {
    if (err) throw err;
    console.log("Connected to a Database!");
});

/* GET home page. */
router.get('/', function(req, res, next) {
  con.query("SELECT * FROM supplies", function (err, result){
      if (err) throw err;
      let orders = result;
      con.query("SELECT * FROM car_models", function (err, result){
          if (err) throw err;
          let cars = result;
          con.query("SELECT * FROM stores", function (err, result){
              if (err) throw err;
              var stores = result;
              let result_orders = [];
              for (let i = 0; i < orders.length; i++){
                  let order;
                  order = orders[i];
                  order.car = find_car(cars, order.model_id);
                  if (order.car.model_electro == 1) order.car.model_electro = 'Yes';
                  else order.car.model_electro = 'No';
                  order.store = find_store(stores, order.store_id);
                  result_orders.push(order);
              }
              res.render('index', {cars: cars, stores: stores, orders: result_orders });
          })
      })
  })
});

router.get('/modifyOrder/:id', function(req, res, next){
    con.query("SELECT * FROM supplies WHERE supply_id=" + req.params.id, function(err, result){
        if (err) throw err;
        var order = result[0];
        con.query("SELECT * FROM car_models", function (err, result){
            if (err) throw err;
            var cars = result;
            con.query("SELECT * FROM stores", function (err, result){
                if (err) throw err;
                var stores = result;
                order.car = find_car(cars, order.model_id);
                order.store = find_store(stores, order.store_id);
                for (let i=0; i<cars.length; i++){
                    if (cars[i].model_id == order.model_id){
                        cars.splice(i, 1);
                        break;
                    }
                }
                for (let i=0; i<stores.length; i++){
                    if (stores[i].store_id == order.store_id){
                        stores.splice(i, 1);
                        break;
                    }
                }
                res.render('modify', {cars: cars, stores: stores, order: order });
            })
        })
    })
})

router.post('/modifyOrder/:id', function(req, res, next){
    con.query("UPDATE supplies" +
        " SET model_id = " + req.body.car_model +
        ", amount = " + req.body.amount +
        ", store_id = " + req.body.store +
        ", price = " + req.body.price +
        " WHERE supply_id = " + req.params.id, function (err, result){
        if (err) throw err;
        res.redirect('/');
    })
})

router.post('/createOrder', function(req, res, next){
    con.query("INSERT INTO supplies (model_id, amount, store_id, price) VALUES(" + req.body.car_model + ", " + req.body.amount + ", " + req.body.store + ", " + req.body.price + ")", function (err, result){
        if (err) throw err;
        console.log("1 order inserted");
    })
    res.redirect('/');
})

router.post('/deleteOrder', function (req, res, next) {
    con.query("DELETE FROM supplies WHERE supply_id="+ req.body.supply_id, function(err, result){
        if (err) throw err;
        console.log(result.rowsAffected + " records deleted");
    })
    res.redirect('/');
})

router.get('/cars', function(req, res, next){
    con.query("SELECT * FROM car_models", function (err, result){
        if (err) throw err;
        for (let i=0; i < result.length; i++){
            if (result[i].model_electro == 1) result[i].model_electro = 'Yes';
            else result[i].model_electro = 'No';
        }
        res.render('cars', {models: result});
    })
})

router.post('/cars', function(req, res, next){
    let from_year = req.body.from_year.slice(0, -6);
    let to_year = req.body.to_year.slice(0, -6);
    let electro;
    if(req.body.electro){
        electro="";
        if (req.body.electro == 1) electro=" AND model_electro=1 ";
        if (req.body.electro == 0) electro=" AND model_electro=0 ";
    }
    console.log(from_year + " to " + to_year);
    let query="SELECT * FROM car_models WHERE model_year>=" + from_year + " AND model_year<=" + to_year + electro;
    console.log(query);
    con.query(query, function(err, result){
        if (err) throw err;
        for (let i=0; i < result.length; i++){
            if (result[i].model_electro == 1) result[i].model_electro = 'Yes';
            else result[i].model_electro = 'No';
        }
        res.render('cars', {models: result});
    })


})

router.post('/search', function(req, res, next){
    let search_key = req.body.search;
    let search_type = req.body.search_type;
    console.log(req.body.search_type);
    let query="";
    let against="";
    if (search_type == "no_word") {
        query += "SELECT * FROM car_models WHERE NOT MATCH(model_name, model_description) AGAINST (";
        query += "'" + search_key + "'";
    }
    else {
        query += "SELECT * FROM car_models WHERE MATCH(model_name, model_description) AGAINST (";
        query += "'\"" + search_key + "\"'"
    }
    query+= " IN BOOLEAN MODE)";
    console.log(query);
    con.query(query, function (err, result){
        if (err) throw err;
        res.render('cars', {models: result});
    })
})

router.get('/updateDimensions', function(req, res, next){
    read("cars.json")
        .then(data => {
            let cars = JSON.parse(data.toString().trim());
            for (let i = 0; i < cars.length; i++){
                con.query("UPDATE car_models" +
                    " SET model_name = '" + cars[i].model_name +
                    "', model_year = " + cars[i].model_year +
                    ", model_description = '" + cars[i].model_description +
                    "', model_electro = " + cars[i].model_electro +
                    " WHERE model_id = " + cars[i].model_id, function (err, result){
                    if (err) throw err;
                })
            }
        })
        .catch(err=>{
            console.log(err.toString().trim());
        });
    read("stores.json")
        .then(data => {
            let stores = JSON.parse(data.toString().trim());
            for (let i = 0; i < stores.length; i++){
                con.query("UPDATE stores" +
                    " SET store_name = '" + stores[i].store_name +
                    "', store_city = '" + stores[i].store_city +
                    "' WHERE store_id = " + stores[i].store_id, function (err, result){
                    if (err) throw err;
                })
            }
        })
        .catch(err=>{
            console.log(err.toString().trim());
        });

    res.redirect('/');
});

router.get('/writefile', function (req, res, next) {
    con.query("SELECT * FROM stores", function (err, result) {
        if (err) throw err;
        let json_string = JSON.stringify(result);
        fs.writeFile("stores.json", json_string);
    });
    con.query("SELECT * FROM car_models", function (err, result) {
        if (err) throw err;
        let json_string = JSON.stringify(result);
        fs.writeFile("cars.json", json_string);
        res.redirect('/')
    });
})



function read(fileName){
    return new Promise(function(resolve, reject){
        fs.readFile(fileName, (err, buf) => {
            if (err) {
                reject(String(err));
            }
            else {
                resolve(String(buf).trim());
            }
        })
    })
}

function find_car(cars, id){
    for (let i = 0; i < cars.length; i++){
        if (cars[i].model_id == id) return cars[i];
    }
}
function find_store(stores, id){
    for (let i = 0; stores.length; i++){
        if (stores[i].store_id == id) return stores[i];
    }
}

module.exports = router;
