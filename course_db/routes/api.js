var express = require('express');
var router = express.Router();
var Company = require('../public/database/database').Company;
var User = require('../public/database/database').User;
var Reference = require('../public/database/database').Reference;

router.get('/companies/delete/*', function(req, res){
    let key = req.path;
    key = key.slice(18);
    Company.findOneAndRemove({code: key}, (err, result) => {
        if (err) res.render('error', {message: err.message, error: err});
        else res.send('ok');
    });
})

router.post('/companies/add', function(req, res, next){
    let company = new Company({
        name: req.query.name,
        code: req.query.code,
        date: new Date(Date.now()),
        address: req.query.address,
        activity_type: req.query.activity_type,
        ownership_type: req.query.ownership_type
    });
    company.save(function(err){
        if (err) res.send('error');
        else res.send('ok');
    });
})

router.get('/companies/find', function(req, res, next){
    Company.findOne({code: req.query.code}, (err, result) => {
        if (err) res.end();
        else res.send(JSON.stringify({user: req.user, company: result}));
    })
})

router.get('/companies/all', function(req, res){
    Company.find({}, (err, companies) => {
        if (err) res.render('error', {message: err.message, error: err});
        else res.send(JSON.stringify(companies));
    });
})

router.get('/references/add', function (req, res, next) {
    Company.find({code: req.query.code}, (err, company)=>{
        if (err) res.end();
        let reference = new Reference ({
            company_code: req.query.code,
            status: 'Очікує затвердження',
            date: new Date(Date.now())
        })
        reference.save(function(err, ref){
            if (err) res.end();
            res.send(JSON.stringify(ref));
        })
    })
})

router.get('/references/find', function(req, res, next){
    Reference.findById(req.query.ref_id, (err, reference) => {
        if (err) res.end();
        if (reference) res.send(JSON.stringify(reference));
        else res.end();
    })
})

module.exports = router;