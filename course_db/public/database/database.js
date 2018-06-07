var express = require('express');
var mongoose = require('mongoose');
var mongoUrl = 'mongodb://localhost:27017/registry';
var db = mongoose.connection;
var ObjectId = mongoose.Schema.ObjectId;
var bcrypt   = require('bcrypt-nodejs');

db.on('error', console.error);
db.once('open', function(){});

mongoose.connect(mongoUrl);

var company = new mongoose.Schema({
    name: {
        type: String,
        required: true
    },
    code: {
        type: Number,
        required: true,
        unique: true
    },
    date: {
        type: Date
    },
    address: {
        type: String,
        required: true
    },
    activity_type: {
        type: String,
        required: true
    },
    ownership_type: {
        type: String,
        required: true
    }
})
var user = new mongoose.Schema({
    name: {
        type: String,
        required: true
    },
    mail: {
        type: String,
        required: true
    },
    password: {
        type: String,
        required: true
    },
    status: {
        type: String,
        default: 'user'
    }
})
var reference = new mongoose.Schema({
    company_code: {
        type: Number,
        required: true
    },
    status: {
        type: String,
        required: true
    },
    date: {
        type: Date
    }
})
user.methods.generateHash = function(password) {
    return bcrypt.hashSync(password, bcrypt.genSaltSync(8), null);
};
user.methods.validPassword = function(password) {
    return bcrypt.compareSync(password, this.password);
};


var User = mongoose.model('User', user);
var Company = mongoose.model('Company', company);
var Reference = mongoose.model('Reference', reference);

module.exports.Company = Company;
module.exports.User = User;
module.exports.Reference = Reference;