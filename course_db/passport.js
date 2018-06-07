var LocalStrategy = require('passport-local').Strategy;
var User = require('./public/database/database').User;

module.exports = function (passport) {
    // serialize user for the session
    passport.serializeUser(function(user, done){
        done(null, user.id);
    })
    // deserialize user for the session
    passport.deserializeUser(function(id, done){
        User.findById(id, function(err, user){
            done(err, user);
        })
    })
    // sign in
    passport.use('local-login', new LocalStrategy({
        usernameField: 'mail',
        passwordField: 'password',
        passReqToCallback: true
    },
    function(req, mail, password, done){
        //callback with mail and password from a form
        //find a user with such mail, check if he exsists
        User.findOne({ 'mail': mail}, function (err, user){
            if (err) return done(err);
            if (!user) return done(null, false, req.flash('loginMessage', 'Не існує користувача з такою поштою'));
            if (!user.validPassword(password)) return done(null, false, req.flash('loginMessage', 'Неправильний пароль'));
            return done(null, user);
        });
    }));
}