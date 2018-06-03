package com.capirott.erick.veeraschat.models;

import java.util.Collection;

public class ChatConversation {

    String id;

    Collection<String> usersId;

    Collection<String> usersKey;


    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public Collection<String> getUsersId() {
        return usersId;
    }

    public void setUsersId(Collection<String> usersId) {
        this.usersId = usersId;
    }

    public Collection<String> getUsersKey() {
        return usersKey;
    }

    public void setUsersKey(Collection<String> usersKey) {
        this.usersKey = usersKey;
    }
}
