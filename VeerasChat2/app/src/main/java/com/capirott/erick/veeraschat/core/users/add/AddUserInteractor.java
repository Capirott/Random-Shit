package com.capirott.erick.veeraschat.core.users.add;

import android.content.Context;
import android.support.annotation.NonNull;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.models.User;
import com.capirott.erick.veeraschat.utils.Constants;
import com.capirott.erick.veeraschat.utils.SharedPrefUtil;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class AddUserInteractor implements AddUserContract.Interactor {
    private AddUserContract.OnUserDatabaseListener mOnUserDatabaseListener;

    public AddUserInteractor(AddUserContract.OnUserDatabaseListener onUserDatabaseListener) {
        this.mOnUserDatabaseListener = onUserDatabaseListener;
    }

    @Override
    public void addUserToDatabase(final Context context, final User user) {
        final DatabaseReference database = FirebaseDatabase.getInstance().getReference();
        user.setFirebaseToken(new SharedPrefUtil(context).getString(Constants.ARG_FIREBASE_TOKEN));
        database.child(Constants.ARG_USERS)
                .child(user.getUid())
                .setValue(user)
                .addOnCompleteListener(new OnCompleteListener<Void>() {
                    @Override
                    public void onComplete(@NonNull Task<Void> task) {
                        if (task.isSuccessful()) {
                            mOnUserDatabaseListener.onSuccess(context.getString(R.string.user_successfully_added));
                            database.child("userCount").addListenerForSingleValueEvent(new ValueEventListener() {
                                @Override
                                public void onDataChange(DataSnapshot dataSnapshot) {
                                    Integer value = dataSnapshot.getValue(Integer.class);
                                    if (value == null) {
                                        value = 1;
                                    }
                                    dataSnapshot.getRef().setValue(value + 1);
                                    String nickname = "Anon#" + String.format("%04d", value);
                                    new SharedPrefUtil(context).saveString(Constants.CURRENTLY_USER_NICKNAME, nickname);
                                    user.setNickname(nickname);
                                    database.child(Constants.ARG_USERS)
                                            .child(user.getUid())
                                            .setValue(user);
                                }

                                @Override
                                public void onCancelled(DatabaseError databaseError) {

                                }
                            });
                        } else {
                            mOnUserDatabaseListener.onFailure(context.getString(R.string.user_unable_to_add));
                        }
                    }
                });
    }
}
