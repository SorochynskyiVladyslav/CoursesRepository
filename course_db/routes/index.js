var express = require('express');
var router = express.Router();
var Company = require('../public/database/database').Company;
var User = require('../public/database/database').User;
var Reference = require('../public/database/database').Reference;

router.get('/', function(req, res, next) {
  Company.find({}, (err, companies) => {
      if (err) res.render('error', {message: err.message, error: err});
      else res.render('index', { user: req.user, companies: companies });
  });
});

router.get('/references', function (req, res, next) {
    if (!req.user || req.user.status != 'owner') res.redirect('/');
    let query = Reference.find();
    query.sort({date: 1});
    query.exec((err, references)=>{
        if (err) res.render('error', {message: err.message, error: err});
        else res.render('references', {user: req.user, references: references});
    });
});

router.get('/users', function(req, res, next){
    User.find({}, (err, users) => {
        if (err) res.render('error', {message: err.message, error: err});
        else res.render('users', { user: req.user, users: users });
    });
})

router.get('/edit_user/*', function(req, res, next){
    if (!req.user || req.user.status != 'owner') res.redirect('/');
    let id = req.path.slice(11);

    User.findByIdAndUpdate(id, {$set: {status: req.query.status}}, (err)=>{
        if (err) res.render('error', {message : err.message, error:err});
        else res.redirect('/users');
    })
})

router.get('/delete_user/*', function(req, res, next){
    if (!req.user || req.user.status != 'owner') res.redirect('/');
    let id = req.path.slice(13);
    User.findByIdAndRemove(id, (err)=>{
        if (err) res.render('error', {message : err.message, error:err});
        else res.redirect('/users');
    })
})

router.get('/edit_reference/*', function(req, res, next){
    if (!req.user || req.user.status != 'owner') res.redirect('/');
    let id = req.path.slice(16);

    Reference.findByIdAndUpdate(id, {$set: {status: req.query.status}}, (err)=>{
        if (err) res.render('error', {message : err.message, error:err});
        else res.redirect('/references');
    })
})

router.get('/delete_reference/*', function(req, res, next){
    if (!req.user || req.user.status != 'owner') res.redirect('/');
    let id = req.path.slice(18);
    Reference.findByIdAndRemove(id, (err)=>{
        if (err) res.render('error', {message : err.message, error:err});
        else res.redirect('/references');
    })
})

router.get('/edit_company/*', function(req, res, next){
    if (!req.user || req.user.status != 'owner') res.redirect('/');
    var key = req.path;
    key = key.slice(14);
    Company.findById(key, (err, company) => {
        if (err) res.render('error', {message : err.message, error:err});
        else res.render('company', {company : company, user: req.user});
    });
});

router.post('/edit_company/*', function(req, res, next){
    if (!req.user || req.user.status != 'owner') res.redirect('/');
    var key = req.path;
    key = key.slice(14);
    Company.findByIdAndUpdate(key, {$set: {name: req.body.name, address: req.body.address, activity_type: req.body.activity_type, ownership_type: req.body.ownership_type}}, (err) => {
        if (err) res.render('error', {message : err.message, error:err});
        else res.redirect('/');
    });
});

module.exports = router;
