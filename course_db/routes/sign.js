module.exports = function(app, passport) {
    var Company = require('../public/database/database').Company;
    var User = require('../public/database/database').User;
    var bcrypt = require('bcrypt-nodejs');


    app.get('/sign/up', function (req, res, next) {
        res.render('sign', {target: 'signUp', message: ''});
    });

    app.post('/sign/up', function (req, res, next) {
        var message;
        User.findOne({'mail': req.body.mail}, function (err, user) {
            if (err) return err;
            if (user) res.render('sign', {target: 'signUp', message: 'Користувач з такою поштою уже зареєстрований.'});
            else {
                var newUser = new User();
                newUser.mail = req.body.mail;
                newUser.password = newUser.generateHash(req.body.password);
                newUser.name = req.body.name;
                newUser.status = 'user';
                newUser.save(function (err) {
                    if (err) res.render('error', {message: err.message, error: err});
                });
                res.redirect('/sign/in');
            }
        })
    })

    app.get('/sign/in', function (req, res, next) {
        res.render('sign', {target: 'signIn', message: req.flash('loginMessage')});
    })

    app.post('/sign/in', passport.authenticate('local-login', {
        successRedirect: '/', // redirect to the secure profile section
        failureRedirect: '/sign/in', // redirect back to the signup page if there is an error
        failureFlash: true // allow flash messages
    }))

    app.get('/sign/out', function(req, res, next){
        req.logout();
        res.redirect('/');
    })
}
