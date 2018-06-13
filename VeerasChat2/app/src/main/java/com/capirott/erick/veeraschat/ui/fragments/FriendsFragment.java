package com.capirott.erick.veeraschat.ui.fragments;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.core.friend.get.all.GetFriendsContract;
import com.capirott.erick.veeraschat.core.friend.get.all.GetFriendsPresenter;
import com.capirott.erick.veeraschat.models.User;
import com.capirott.erick.veeraschat.ui.activities.ChatActivity;
import com.capirott.erick.veeraschat.ui.adapters.FriendListingRecyclerAdapter;
import com.capirott.erick.veeraschat.utils.ItemClickSupport;
import com.google.firebase.auth.FirebaseAuth;

import java.util.List;


public class FriendsFragment extends Fragment implements GetFriendsContract.View, ItemClickSupport.OnItemClickListener, SwipeRefreshLayout.OnRefreshListener {
    public static final String ARG_TYPE = "type";
    public static final String TYPE_CHATS = "type_chats";
    public static final String TYPE_ALL = "type_all";

    private SwipeRefreshLayout mSwipeRefreshLayout;
    private RecyclerView mRecyclerViewAllFriendsListing;

    private FriendListingRecyclerAdapter mFriendListingRecyclerAdapter;

    private GetFriendsPresenter mGetFriendsPresenter;

    public static FriendsFragment newInstance(String type) {
        Bundle args = new Bundle();
        args.putString(ARG_TYPE, type);
        FriendsFragment fragment = new FriendsFragment();
        fragment.setArguments(args);
        return fragment;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View fragmentView = inflater.inflate(R.layout.fragment_users, container, false);
        bindViews(fragmentView);
        return fragmentView;
    }

    private void bindViews(View view) {
        mSwipeRefreshLayout = (SwipeRefreshLayout) view.findViewById(R.id.swipe_refresh_layout);
        mRecyclerViewAllFriendsListing = (RecyclerView) view.findViewById(R.id.recycler_view_all_user_listing);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        init();
    }

    private void init() {
        mGetFriendsPresenter = new GetFriendsPresenter(this);
        getFriends();
        mSwipeRefreshLayout.post(new Runnable() {
            @Override
            public void run() {
                mSwipeRefreshLayout.setRefreshing(true);
            }
        });

        ItemClickSupport.addTo(mRecyclerViewAllFriendsListing)
                .setOnItemClickListener(this);

        mSwipeRefreshLayout.setOnRefreshListener(this);
    }

    @Override
    public void onRefresh() {
        getFriends();
    }

    private void getFriends() {
        if (TextUtils.equals(getArguments().getString(ARG_TYPE), TYPE_CHATS)) {

        } else if (TextUtils.equals(getArguments().getString(ARG_TYPE), TYPE_ALL)) {
            mGetFriendsPresenter.getAllFriends(FirebaseAuth.getInstance().getCurrentUser().getUid());
        }
    }

    @Override
    public void onItemClicked(RecyclerView recyclerView, int position, View v) {
        User user = mFriendListingRecyclerAdapter.getUser(position);
        ChatActivity.startActivity(getActivity(), user);
    }

    @Override
    public void onGetAllFriendsSuccess(List<User> users) {
        mSwipeRefreshLayout.post(new Runnable() {
            @Override
            public void run() {
                mSwipeRefreshLayout.setRefreshing(false);
            }
        });
        mFriendListingRecyclerAdapter = new FriendListingRecyclerAdapter(users);
        mRecyclerViewAllFriendsListing.setAdapter(mFriendListingRecyclerAdapter);
        mFriendListingRecyclerAdapter.notifyDataSetChanged();
    }

    @Override
    public void onGetAllFriendsFailure(String message) {
        mSwipeRefreshLayout.post(new Runnable() {
            @Override
            public void run() {
                mSwipeRefreshLayout.setRefreshing(false);
            }
        });
        Toast.makeText(getActivity(), "Error: " + message, Toast.LENGTH_SHORT).show();
    }
}
