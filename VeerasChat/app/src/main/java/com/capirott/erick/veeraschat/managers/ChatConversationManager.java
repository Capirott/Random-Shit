package com.capirott.erick.veeraschat.managers;

import android.util.Log;

import com.capirott.erick.veeraschat.models.ChatConversation;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.List;

public class ChatConversationManager {
    private static final String FIREBASE_REFERENCE = "CONVERSATION";

    static public void save(ChatConversation conversation) {
        FirebaseDatabase.getInstance()
                .getReference(FIREBASE_REFERENCE)
                .push()
                .setValue(conversation
                );
        Log.d("ChatConversationManager", "Conversation created!");

    }

    static public void createOrUpdate(final String id, final Runnable callback) {
        final List<ChatConversation> events = new ArrayList<>();
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference(FIREBASE_REFERENCE);
        ref.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                Log.d("ChatConversationManager", "onDataChange");
                DataSnapshot theOne = null;
                for (DataSnapshot snapshot : dataSnapshot.getChildren()) {
                    ChatConversation event = snapshot.getValue(ChatConversation.class);
                    if (event.getId().equals(id)) {
                        Log.d("ChatConversationManager", "Found conversation!");
                        events.add(event);
                        theOne = snapshot;
                    }
                }
                ChatConversation chatConversation = new ChatConversation();
                if (theOne != null) {
                } else {
                    FirebaseUser currentUser = FirebaseAuth.getInstance().getCurrentUser();
                    chatConversation.setId(id);
                    ChatConversationManager.save(chatConversation);

                }
                if (callback != null) {
                    callback.run();
                }
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }
}
