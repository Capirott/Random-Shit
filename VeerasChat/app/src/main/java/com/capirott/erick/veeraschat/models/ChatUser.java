package com.capirott.erick.veeraschat.models;

import java.util.Collection;

public class ChatUser {

    private String id;

    private String nickname;

    private String email;

    private String password;

    private Collection<String> conversationsId;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public Collection<String> getConversationsId() {
        return conversationsId;
    }

    public void setConversationsId(Collection<String> conversationsId) {
        this.conversationsId = conversationsId;
    }

    public void addConversationId(String id) {
        this.conversationsId.add(id);
    }
}
