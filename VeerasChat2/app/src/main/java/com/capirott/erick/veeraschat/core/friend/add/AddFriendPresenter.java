package com.capirott.erick.veeraschat.core.friend.add;

import android.content.Context;

import com.capirott.erick.veeraschat.models.User;


public class AddFriendPresenter implements AddFriendContract.Presenter, AddFriendContract.OnFriendDatabaseListener {
        private AddFriendContract.View mView;
    private AddFriendInteractor mAddFriendInteractor;

    public AddFriendPresenter(AddFriendContract.View view) {
        this.mView = view;
        mAddFriendInteractor = new AddFriendInteractor(this);
    }

    @Override
    public void addFriend(Context context, User user) {
        mAddFriendInteractor.addFriendToDatabase(context, user);
    }

    @Override
    public void onSuccess(String message) {
        mView.onAddFriendSuccess(message);
    }

    @Override
    public void onFailure(String message) {
        mView.onAddFriendFailure(message);
    }
}
