package com.capirott.erick.veeraschat.core.friend.get;

import android.content.Context;
import android.util.Log;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.utils.Constants;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class GetFriendInteractor implements GetFriendContract.Interactor {

    private static final String TAG = "GetFriendInteractor";

    private GetFriendContract.OnFriendDatabaseListener mOnFriendDatabaseListener;


    public GetFriendInteractor(GetFriendContract.OnFriendDatabaseListener onFriendDatabaseListener) {
        this.mOnFriendDatabaseListener = onFriendDatabaseListener;
    }

    @Override
    public void friendShipExists(final Context context, final String userId, final String userId2) {
        final DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference();

        databaseReference.child(Constants.ARG_USERS).child(userId).child(Constants.ARG_FRIENDS).child(userId2).getRef().addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                Boolean value = dataSnapshot.getValue(Boolean.class);
                if (value != null && value.equals(true)) {
                    mOnFriendDatabaseListener.onSuccess(context.getString(R.string.friend_successfully_returned));
                } else {
                    mOnFriendDatabaseListener.onFailure(context.getString(R.string.friend_unsuccessfully_returned));
                }
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                mOnFriendDatabaseListener.onFailure("Unable to get friend: " + databaseError.getMessage());
            }
        });
    }

}
