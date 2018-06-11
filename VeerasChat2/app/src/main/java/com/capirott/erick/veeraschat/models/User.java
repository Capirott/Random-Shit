package com.capirott.erick.veeraschat.models;


public class User {
    private String uid;
    private String email;
    private String nickname;
    private String firebaseToken;

    public User() {
    }

    public User(String uid, String email, String nickname, String firebaseToken) {
        this.uid = uid;
        this.email = email;
        this.nickname = nickname;
        this.firebaseToken = firebaseToken;
    }

    public String getUid() {
        return uid;
    }

    public void setUid(String uid) {
        this.uid = uid;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getFirebaseToken() {
        return firebaseToken;
    }

    public void setFirebaseToken(String firebaseToken) {
        this.firebaseToken = firebaseToken;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }
}
