package com.capirott.erick.veeraschat.models;

import java.util.Collection;

public class ChatUser {

    private String id;

    private String nickname;

    private boolean isOnline;

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

    public Collection<String> getConversationsId() {
        return conversationsId;
    }

    public void setConversationsId(Collection<String> conversationsId) {
        this.conversationsId = conversationsId;
    }

    public void addConversationId(String id) {
        this.conversationsId.add(id);
    }

    public boolean isOnline() {
        return isOnline;
    }

    public void setOnline(boolean online) {
        isOnline = online;
    }
}
