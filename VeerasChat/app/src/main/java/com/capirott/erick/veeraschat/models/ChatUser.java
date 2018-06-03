package com.capirott.erick.veeraschat.models;

import java.util.Collection;

public class ChatUser {

    String id;

    String name;

    String nickName;

    ChatContactList contactList;

    Collection<String> conversationKeys;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
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
