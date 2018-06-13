package com.capirott.erick.veeraschat.core.friend.get.all;

import com.capirott.erick.veeraschat.models.User;

import java.util.List;


public class GetFriendsPresenter implements GetFriendsContract.Presenter, GetFriendsContract.OnGetAllFriendsListener {
    private GetFriendsContract.View mView;
    private GetFriendsInteractor mGetFriendsInteractor;

    public GetFriendsPresenter(GetFriendsContract.View view) {
        this.mView = view;
        mGetFriendsInteractor = new GetFriendsInteractor(this);
    }

    @Override
    public void getAllFriends(String userId) {
        mGetFriendsInteractor.getAllFriendsFromFirebase(userId);
    }

    @Override
    public void onGetAllFriendsSuccess(List<User> users) {
        mView.onGetAllFriendsSuccess(users);
    }

    @Override
    public void onGetAllFriendsFailure(String message) {
        mView.onGetAllFriendsFailure(message);
    }
}
