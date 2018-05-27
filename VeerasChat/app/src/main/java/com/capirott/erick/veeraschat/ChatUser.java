package com.capirott.erick.veeraschat;

import java.util.Collection;

public class ChatUser {

    String userId;

    String name;

    String nickName;

    ChatContactList contactList;

    Collection<String> conversationKeys;

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getNickName() {
        return nickName;
    }

    public void setNickName(String nickName) {
        this.nickName = nickName;
    }

    public ChatContactList getContactList() {
        return contactList;
    }

    public void setContactList(ChatContactList contactList) {
        this.contactList = contactList;
    }
}
